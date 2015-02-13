/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Junyu wu, shibuyanorailgun@foxmail, 2015.
 */

#include <linux/ctype.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/string.h>

#define __LINUX_ACT_PARSE_C

#include "Asserts.h"
#include "act.h"
#include "parse.h"

int act_parse_int(const char s[], const size_t sz, int *pt)
{
	int i = 0, sg = 1, rv = 0;

	switch (*s)
	{
	case '-':
		sg = -1;

	case '+':
		i++;
		break;
	}

	while (i < sz && isdigit(s[i])) {
		rv = rv * 10 + s[i] - '0';
		i++;
	}
	*pt = rv * sg;

	if (i == 0)
		return -EINVAL;

	return i;
}

/*
 * Remove duplicated spaces from rule buffer.
 *
 * @rule: Raw rule string buffer.
 * @sz: Size of string buffer.
 *
 * @return: 0 on success.
 */
int act_remove_spaces(const char rule[], const size_t sz, char **pbuf)
{
	char *buf;
	size_t i, j;

	buf = kmalloc(sz + 1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	*pbuf = buf;

	i = 0;
	while (isspace(rule[i]))
		i++;

	for (j = 0; i < sz; )
	{
		if (!isspace(rule[i])) {
			buf[j++] = rule[i++];
			continue;
		}

		buf[j++] = ' ';
		while (i < sz && isspace(rule[i]))
			i++;
	}
	buf[j] = 0;
	
	return j;
}

int act_parse_policy_sign(act_policy_t *pl, const char rule[], const size_t sz)
{
	static const act_sign_t signs[] = {
		ACT_ALLOW, ACT_DENY
	};

	int rv;
	
	if (!strncmp(rule, "ALLOW ", 6)) {
		pl->sign = ACT_ALLOW;
		rv = 6;
	}

	else if (!strncmp(rule, "DENY ", 5)) {
		pl->sign = ACT_DENY;
		rv = 5;
	}

	else
		rv = -EINVAL;

	return rv;
}

int act_parse_policy_action(
		act_policy_t *pl, const char rule[], const size_t sz)
{
	int i;

	pl->action = ACT_ACTION_FILE_OPEN;

	for (i = 0; i < sz; i++) {
		if (isspace(rule[i]))
			break;
	}

	if (strncmp(&rule[i], " IF ", 4))
		return -EINVAL;

	return i + 4;
}

int act_parse_separator(const char rule[], const size_t sz)
{
	switch (sz)
	{
	case 0:
		break;

	case 1:
		if (*rule == ';')
			return 1;
		break;

	default:
		if (!strncmp("; ", rule, 2))
			return 2;
	}

	return -EINVAL;
}

int act_parse_single_cond(
		act_cond_t *cond, const char rule[], const size_t sz)
{
	static const char *patterns[] = {
		"= ", "< ", "> ", "IN "
	};

	static const size_t patlens[] = {
		2, 2, 2, 3
	};
	
	static const act_cmp_t cmps[] = {
		ACT_CMP_EQUAL, ACT_CMP_LESS, ACT_CMP_GREATER, ACT_CMP_IN
	};

	act_single_cond_t *single;
	size_t i, j;

	single = &cond->single_cond;

	/* Parses attribute name */

	for (i = 0; i < sz; i++)
	{
		if (rule[i] == ' ')
			break;

		if (!isalpha(rule[i]) && rule[i] != '_')
			return -EINVAL;
	}

	if (!i)
		return -EINVAL;

	single->key = kmalloc(i + 1, GFP_KERNEL);
	if (!single->key)
		return -ENOMEM;
	strncpy(single->key, rule, i);
	single->key[i] = 0;

	/* Parses comparator */

	if (++i >= sz)
		return -EINVAL;

	for (j = 0; j < ARRAY_SIZE(cmps); j++)
	{
		if (!strncmp(&rule[i], patterns[j], patlens[j]))
		{
			single->cmp = cmps[j];
			i += patlens[j];
			break;
		}
	}

	if (j == ARRAY_SIZE(cmps))
		return -EINVAL;

	/* Parses attribute value */

	if (isdigit(rule[i])) {
		single->type = ACT_ATTR_TYPE_INT;
		j = act_parse_int(&rule[i], sz - i, &single->intval);
		if (j < 0)
			return j;
		i += j + 1; /* Skip ' ' */
	}

	else if (rule[i] == '\'') {

	}

	j = act_parse_separator(&rule[i], sz - i);
	if (j < 0)
		return -EINVAL;

	return i + j;
}

/*
 * Parses policy multi-condition ( and, or ).
 *
 * @cond: Condition.
 * @rule: Space removed rule string.
 * @sz: Size of rule string ( without terminating '\0' ).
 *
 * @return: Number of charaters parsed in `rule`.
 * 
 * FIXME: Memory leaks on fail parsing.
 */
int act_parse_multi_conds(
		act_cond_t *cond, const char rule[], const size_t sz)
{
	act_cond_type_t type;
	int i, nchild = 0, rv;
	char lb, rb;

	switch (lb = *rule)
	{
	case '{':
		type = ACT_COND_TYPE_AND;
		rb = '}';
		break;
	
	case '[':
		type = ACT_COND_TYPE_AND;
		rb = ']';
		break;

	default:
		return -EINVAL;
	}

	cond->cond_type = type;

	for (i = 2; i < sz; )
	{
		switch (rule[i])
		{
		case '}':
		case ']':
			ACT_Assert(rule[i] == rb);
			if (i + 2 >= sz)
				return -EINVAL;

			rv = act_parse_separator(&rule[i + 2], sz - i - 2);
			if (rv < 0)
				return rv;

			cond->nconds = nchild;

			return i + 2 + rv; /* { ... } ; */

		case '{':
		case '[':
			if (nchild == ACT_COND_MAX_CHILDREN)
				return -E2BIG;

			cond->conds[nchild] = act_new_cond();
			rv = act_parse_multi_conds(cond->conds[nchild++],
					&rule[i], sz - i);
			if (rv < 0)
				return rv;
			i += rv;

			break;

		default:
			if (nchild == ACT_COND_MAX_CHILDREN)
				return -E2BIG;

			cond->conds[nchild] = act_new_cond();
			rv = act_parse_single_cond(cond->conds[nchild++],
					&rule[i], sz - i);
			if (rv < 0)
				return rv;
			i += rv;

			break;
		}
	}

	return -EINVAL;
}

int act_parse_policy(act_policy_t *pl, const char rawr[], const size_t rsz)
{
	char *r;
	int rv;
	size_t sz;

	rv = act_remove_spaces(rawr, rsz, &r);
	if (rv)
		return rv;
	sz = rv;

	rv = act_parse_policy_sign(pl, r, sz);
	if (rv)
		return rv;

	rv = act_parse_policy_action(pl, r, sz);
	if (rv)
		return rv;

	return 0;
}
