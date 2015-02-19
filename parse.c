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

/*
 * Remove duplicated spaces from rule buffer.
 *
 * @rule: Raw rule string buffer.
 * @sz: Size of string buffer.
 *
 * @return: 0 on success.
 */
#ifndef CONFIG_ACT_TEST
static
#endif
int _tokenize(const char rule[], const size_t sz, char **pbuf)
{
	char *buf;
	size_t i, j;

	buf = kmalloc(sz * 2 + 1, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	*pbuf = buf;

	i = 0;
	while (isspace(rule[i]))
		i++;

	for (j = 0; i < sz; )
	{
		if (isspace(rule[i])) {
			i++;
			continue;
		}

		/* Keyword & variable */
		if (isalpha(rule[i]) || rule[i] == '_')
		{
			while (i < sz &&
					(isalpha(rule[i]) || rule[i] == '_'))
			{
				buf[j++] = rule[i++];
			}
			buf[j++] = ' ';
			continue;
		}

		/* Number */
		if (isdigit(rule[i]))
		{
			while (i < sz && isdigit(rule[i])) {
				buf[j++] = rule[i++];
			}
			buf[j++] = ' ';
			continue;
		}

		/* String */
		if (rule[i] == '\'') {
			buf[j++] = '\'';
			i++;
			while (i < sz && rule[i] != '\'') {
				buf[j++] = rule[i++];
			}
			if (i == sz)
				return -EINVAL;
			buf[j++] = '\'';
			buf[j++] = ' ';
			i++;
			continue;
		}

		/* Operators: . { } [ ] ( ) = < > ~ */
		if (ispunct(rule[i])) {
			buf[j++] = rule[i++];
			buf[j++] = ' ';
			continue;
		}
	}
	buf[j] = 0;
	
	return j;
}

/*
 * Parse integer in rule.
 *
 * @s: Rule string to parse.
 * @sz: Size of buffer.
 * @pt: Stores integer.
 *
 * @return: Length of chars read, -EINVAL on invalid case.
 */
#ifndef CONFIG_ACT_TEST
static
#endif
int _parse_int(
		const char s[], const size_t sz, int *pt)
{
	int i = 0, sg = 0, rv = 0;

	switch (*s)
	{
	case '-':
		sg = 0x80000000;

	case '+':
		i++;
		break;
	}

	while (i < sz && isdigit(s[i])) {
		rv *= 10;
		rv += s[i++] - '0';
	}
	*pt = rv | sg;

	if (i == 0)
		return -EINVAL;

	return i;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int _parse_separator(const char rule[], const size_t sz)
{
	switch (sz)
	{
	case 0:
		break;

	case 1:
		ACT_Assert(0);

	default:
		if (!strncmp("; ", rule, 2))
			return 2;
	}

	return -EINVAL;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int _parse_single_cond(
		act_cond_t *cond, const char rule[], const size_t sz)
{
	static const char *patterns[] = {
		"= ", "< ", "> ", "~ "
	};

	static const size_t patlens[] = {
		2, 2, 2, 3
	};
	
	static const act_cmp_t cmps[] = {
		ACT_CMP_EQUAL, ACT_CMP_LESS, ACT_CMP_GREATER, ACT_CMP_IN
	};

	act_single_cond_t *single;
	size_t i, j;
	int rv;

	single = &cond->single_cond;

	/* Parses owner */

	if (!strncmp(rule, "SUBJECT . ", 10)) {
		single->owner = ACT_OWNER_SUBJ;
		i = 10;
	}
	else if (!strncmp(rule, "OBJECT . ", 9)) {
		single->owner = ACT_OWNER_OBJ;
		i = 9;
	}
	else
		return -EINVAL;

	/* Parses attribute name */

	for (j = i; j < sz; j++)
	{
		if (rule[j] == ' ')
			break;

		if (!isalpha(rule[j]) && rule[j] != '_')
			return -EINVAL;
	}

	single->key = kmalloc(j - i + 1, GFP_KERNEL);
	if (!single->key)
		return -ENOMEM;
	strncpy(single->key, rule + i, j - i);
	single->key[j - i] = 0;

	/* Parses comparator */

	i = j;
	if (++i >= sz) {
		rv = -EINVAL;
		goto out_free_key;
	}

	for (j = 0; j < ARRAY_SIZE(cmps); j++)
	{
		if (!strncmp(&rule[i], patterns[j], patlens[j]))
		{
			single->cmp = cmps[j];
			i += patlens[j];
			break;
		}
	}

	if (j == ARRAY_SIZE(cmps)) {
		rv = -EINVAL;
		goto out_free_key;
	}

	/* Parses attribute value */

	if (isdigit(rule[i])) {
		single->type = ACT_ATTR_TYPE_INT;
		j = _parse_int(&rule[i], sz - i, &single->intval);
		if (j < 0)
			return j;
		i += j + 1;
	}

	else if (rule[i] == '\'') {
		single->type = ACT_ATTR_TYPE_STR;

		j = i + 1;
		while (j < sz && rule[j] != '\'')
			j++;
		single->strval = kmalloc(j - i, GFP_KERNEL);
		if (!single->strval)
			return -ENOMEM;
		strncpy(single->strval, rule + i + 1, j - i - 1);
		single->strval[j - i - 1] = 0;

		i = j + 2;
	}

	j = _parse_separator(&rule[i], sz - i);
	if (j < 0) {
		rv = -EINVAL;
		goto out_free_vals;
	}

	return i + j;

out_free_vals:

out_free_key:
	if (single->key) {
		kfree(single->key);
	}

	return rv;
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
#ifndef CONFIG_ACT_TEST
static
#endif
int _parse_multi_conds(
		act_cond_t *cond, const char rule[], const size_t sz)
{
	act_cond_type_t type;
	int i, rv = -EINVAL;
	char lb, rb;

	switch (lb = *rule)
	{
	case '{':
		type = ACT_COND_TYPE_AND;
		rb = '}';
		break;
	
	case '[':
		type = ACT_COND_TYPE_OR;
		rb = ']';
		break;

	default:
		return -EINVAL;
	}

	cond->cond_type = type;
	cond->nconds = 0;

	for (i = 2; i < sz; )
	{
		switch (rule[i])
		{
		case '}':
		case ']':
			ACT_Assert(rule[i] == rb);
			if (i + 2 >= sz) {
				rv = -EINVAL;
				goto out_free_cond;
			}

			rv = _parse_separator(&rule[i + 2], sz - i - 2);
			if (rv < 0)
				return rv;

			return i + 2 + rv; /* { ... } ; */

		case '{':
		case '[':
			if (cond->nconds == ACT_COND_MAX_CHILDREN) {
				rv = -E2BIG;
				goto out_free_cond;
			}

			cond->conds[cond->nconds] = act_new_cond();
			rv = _parse_multi_conds(cond->conds[cond->nconds++],
					&rule[i], sz - i);
			if (rv < 0) {
				goto out_free_cond;
			}
			i += rv;

			break;

		default:
			if (cond->nconds == ACT_COND_MAX_CHILDREN)
				return -E2BIG;

			cond->conds[cond->nconds] = act_new_cond();
			rv = _parse_single_cond(cond->conds[cond->nconds++],
					&rule[i], sz - i);
			if (rv < 0) {
				goto out_free_cond;
			}
			i += rv;

			break;
		}
	}

out_free_cond:
	act_destroy_cond(cond);

	return rv;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int _parse_policy_sign(act_policy_t *pl, const char rule[], const size_t sz)
{
	int rv;
	
	if (!strncmp(rule, "ALLOW ", 6)) {
		pl->sign = ACT_SIGN_ALLOW;
		rv = 6;
	}

	else if (!strncmp(rule, "DENY ", 5)) {
		pl->sign = ACT_SIGN_DENY;
		rv = 5;
	}

	else
		rv = -EINVAL;

	return rv;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int _parse_policy_action(
		act_policy_t *pl, const char rule[], const size_t sz)
{
	size_t i;

	pl->action = ACT_ACTION_FILE_OPEN;

	for (i = 0; i < sz; i++) {
		if (isspace(rule[i]))
			break;
	}

	pl->action = act_str_action(rule, i);
	if (pl->action == ACT_ACTION_UNKNOWN)
		return -EINVAL;

	if (strncmp(&rule[i], " IF ", 4))
		return -EINVAL;

	return i + 4;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int act_parse_policy(act_policy_t *pl, const char rr[], const size_t rsz)
{
	char *r;
	int rv, i;
	size_t sz;

	rv = _tokenize(rr, rsz, &r);
	if (rv < 0)
		goto out;
	sz = rv;

	rv = _parse_policy_sign(pl, r, sz);
	if (rv < 0)
		goto out;
	i = rv;

	rv = _parse_policy_action(pl, r + i, sz - i);
	if (rv < 0)
		goto out;
	i += rv;

	rv = _parse_multi_conds(&pl->cond, r + i, sz - i);
	if (rv < 0)
		goto out;

	return i + rv;

out:
	if (r)
		kfree(r);

	return rv;
}
