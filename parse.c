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
 * Copyright (C) Junyu wu, shibuyanorailgun@foxmail, 2014.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/string.h>

#include "act.h"
#include "policy.h"

int act_str_sec_lv(const char *tok, enum act_sec_lv *slev)
{
	if (!strcmp(tok, "TRIVIAL"))
		*slev = ACT_TRIVIAL;

	else if (!strcmp(tok, "ROUTINE"))
		*slev = ACT_ROUTINE;

	else if (!strcmp(tok, "SYSTEMATIC"))
		*slev = ACT_SYSTEMATIC;

	else if (!strcmp(tok, "SECRET"))
		*slev = ACT_SECRET;

	else
		return -EINVAL;

	return strlen(tok) + 1;
}
EXPORT_SYMBOL(act_str_sec_lv);

int act_str_role(const char *tok, enum act_role *role)
{
	if (!strcmp(tok, "GUEST"))
		*role = ACT_GUEST;

	else if (!strcmp(tok, "USER"))
		*role = ACT_USER;

	else if (!strcmp(tok, "ADMIN"))
		*role = ACT_ADMIN;

	else if (!strcmp(tok, "SUPERROOT"))
		*role = ACT_SUPERROOT;

	else
		return -EINVAL;

	return strlen(tok) + 1;
}
EXPORT_SYMBOL(act_str_role);

int act_str_cmp(const char *tok, enum act_cmp *cmp)
{
	if (!strcmp("=", tok))
		*cmp = ACT_EQUAL;

	else if (!strcmp("<=", tok))
		*cmp = ACT_LESS_EQUAL;

	else if (!strcmp(">=", tok))
		*cmp = ACT_GREATER_EQUAL;

	else
		return -EINVAL;

	return strlen(tok) + 1;
}
EXPORT_SYMBOL(act_str_cmp);

int act_str_action(const char *tok, enum act_action *act)
{
	*act = ACT_ACTION_FILE_PERMISSION;

	return strlen(tok) + 1;
}
EXPORT_SYMBOL(act_str_action);

int act_str_sign(const char *tok, enum act_sign *sign)
{
	if (!strcmp("NOT_APPLICABLE", tok))
		*sign = ACT_NOT_APPLICABLE;

	else if (!strcmp("DENY", tok))
		*sign = ACT_DENY;

	else if (!strcmp("ALLOW", tok))
		*sign = ACT_ALLOW;

	else
		return -EINVAL;

	return strlen(tok) + 1;
}
EXPORT_SYMBOL(act_str_sign);

int act_str_separator(const char *tok, int *skip)
{
	if (!strcmp(",", tok))
		*skip = 0;

	else if (!strcmp(";", tok))
		*skip = !0;

	else
		return -EINVAL;

	return strlen(tok) + 1;
}
EXPORT_SYMBOL(act_str_separator);

static
int act_sec_lv_cond_parse(const char *tok, struct list_head *conds)
{
	const char *_tok = tok;
	int rv, skip;
	struct act_sec_lv_cond *cond;

	tok += strlen(tok) + 1; /* "(SUBJECT|OBJECT)_SECURITY_LEVEL" */

	do {
		cond = kmalloc(sizeof(struct act_sec_lv_cond), GFP_KERNEL);
		if (!cond)
			return -ENOMEM;

		rv = act_str_cmp(tok, &cond->cmp);
		if (rv < 0)
			goto out_free_cond;
		tok += rv;

		rv = act_str_sec_lv(tok, &cond->slv);
		if (rv < 0)
			goto out_free_cond;
		tok += rv;

		rv = act_str_separator(tok, &skip);
		if (rv < 0)
			goto out_free_cond;
		tok += rv;

		list_add(&cond->list, conds);
	} while (!skip);

	return tok - _tok;

out_free_cond:
	if (cond)
		kfree(cond);
	return -EINVAL;
}

static
int act_role_cond_parse(const char *tok, struct list_head *conds)
{
	const char *_tok = tok;
	int rv, skip;
	struct act_role_cond *cond;

	tok += strlen(tok) + 1; /* "(SUBJECT|OBJECT)_SECURITY_ROLE" */

	do {
		cond = kmalloc(sizeof(struct act_sec_lv_cond), GFP_KERNEL);
		if (!cond)
			return -ENOMEM;

		rv = act_str_cmp(tok, &cond->cmp);
		if (rv < 0)
			goto out_free_cond;
		tok += rv;

		rv = act_str_role(tok, &cond->role);
		if (rv < 0)
			goto out_free_cond;
		tok += rv;

		rv = act_str_separator(tok, &skip);
		if (rv < 0)
			goto out_free_cond;
		tok += rv;

		list_add(&cond->list, conds);
	} while (!skip);

	return tok - _tok;

out_free_cond:
	if (cond)
		kfree(cond);
	return -EINVAL;
}

static
int act_action_cond_parse(const char *tok, enum act_action *act)
{
	enum act_cmp cmp;
	const char *_tok = tok;
	int rv, skip;

	tok += strlen(tok) + 1; /* "ACTION" */

	rv = act_str_cmp(tok, &cmp);
	if (rv < 0 || cmp != ACT_EQUAL)
		return -EINVAL;
	tok += rv;

	rv = act_str_action(tok, act);
	if (rv < 0)
		return -EINVAL;
	tok += rv;

	rv = act_str_separator(tok, &skip);
	if (rv < 0)
		return -EINVAL;
	tok += rv;

	return tok - _tok;
}

static
int act_sign_cond_parse(const char *tok, enum act_sign *sign)
{
	enum act_cmp cmp;
	const char *_tok = tok;
	int rv, skip;

	tok += strlen(tok) + 1; /* "ACTION" */

	rv = act_str_cmp(tok, &cmp);
	if (rv < 0 || cmp != ACT_EQUAL)
		return -EINVAL;
	tok += rv;

	rv = act_str_sign(tok, sign);
	if (rv < 0)
		return -EINVAL;
	tok += rv;

	rv = act_str_separator(tok, &skip);
	if (rv < 0)
		return -EINVAL;
	tok += rv;

	return tok - _tok;
}

int act_policy_parse(struct act_policy *pl,
		const char *rule, const size_t rulesz)
{
	size_t i = 0, rv;

	act_init_policy(pl, 0, 0);

	while (i < rulesz) {
		if (!strcmp("SUBJECT_SECURITY_LEVEL", rule + i)) {
			rv = act_sec_lv_cond_parse(rule + i, &pl->sslv_conds);
		}
		
		else if (!strcmp("SUBJECT_SECURITY_ROLE", rule + i)) {
			rv = act_role_cond_parse(rule + i, &pl->srole_conds);
		}

		else if (!strcmp("OBJECT_SECURITY_LEVEL", rule + i)) {
			rv = act_sec_lv_cond_parse(rule + i, &pl->oslv_conds);
		}

		else if (!strcmp("OBJECT_SECURITY_ROLE", rule + i)) {
			rv = act_role_cond_parse(rule + i, &pl->orole_conds);
		}

		else if (!strcmp("ACTION", rule + i)) {
			rv = act_action_cond_parse(rule + i, &pl->action);
		}

		else if (!strcmp("SIGN", rule + i)) {
			rv = act_sign_cond_parse(rule + i, &pl->sign);
		}
		
		else {
			return -EINVAL;
		}

		if (rv < 0)
			return rv;
		i += rv;
	}

	return 0;
}
EXPORT_SYMBOL(act_policy_parse);
