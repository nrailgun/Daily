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
#include <linux/list.h>
#include <linux/slab.h>

#include "act.h"
#include "policy.h"

LIST_HEAD(act_policies);

const char *act_sec_lv_str(enum act_sec_lv lv)
{
	switch (lv)
	{
	case ACT_TRIVIAL:
		return "TRIVIAL";

	case ACT_ROUTINE:
		return "ROUTINE";

	case ACT_SYSTEMATIC:
		return "SYSTEMATIC";

	case ACT_SECRET:
		return "SECRET";

	default:
		return NULL;
	}
}
EXPORT_SYMBOL(act_sec_lv_str);

const char *act_role_str(const enum act_role role)
{
	switch (role)
	{
	case ACT_GUEST:
		return "GUEST";

	case ACT_USER:
		return "USER";

	case ACT_ADMIN:
		return "ADMIN";

	case ACT_SUPERROOT:
		return "SUPERROOT";

	default:
		return NULL;
	}
}
EXPORT_SYMBOL(act_role_str);

const char *act_cmp_str(enum act_cmp cmp)
{
	switch (cmp)
	{
	case ACT_EQUAL:
		return "=";

	case ACT_LESS_EQUAL:
		return "<=";

	case ACT_GREATER_EQUAL:
		return ">=";

	default:
		return NULL;
	}
}
EXPORT_SYMBOL(act_cmp_str);

const char *act_action_str(const enum act_action act)
{
	return "UNKNOWN_ACTION";
}
EXPORT_SYMBOL(act_action_str);

const char *act_sign_str(const enum act_sign sign)
{
	switch (sign)
	{
	case ACT_NOT_APPLICABLE:
		return "NOT_APPLICABLE";
	case ACT_DENY:
		return "DENY";
	case ACT_ALLOW:
		return "ALLOW";
	default:
		return NULL;
	}
}
EXPORT_SYMBOL(act_sign_str);

void act_init_subj_ctx(struct act_subj_ctx *ctx,
		const enum act_sec_lv slv, const enum act_role role)
{
	ctx->sslv = slv;
	ctx->srole = role;
}
EXPORT_SYMBOL(act_init_subj_ctx);

void act_init_obj_ctx(struct act_obj_ctx *ctx,
		const enum act_sec_lv slv, const enum act_role role)
{
	ctx->oslv = slv;
	ctx->orole = role;
}
EXPORT_SYMBOL(act_init_obj_ctx);

void act_init_sec_lv_cond(struct act_sec_lv_cond *cond,
		const enum act_cmp cmp, const enum act_sec_lv slv)
{
	cond->cmp = cmp;
	cond->slv = slv;
	INIT_LIST_HEAD(&cond->list);
}
EXPORT_SYMBOL(act_init_sec_lv_cond);

void act_init_role_cond(struct act_role_cond *cond,
		const enum act_cmp cmp, const enum act_role role)
{
	cond->cmp = cmp;
	cond->role = role;
	INIT_LIST_HEAD(&cond->list);
}
EXPORT_SYMBOL(act_init_role_cond);

void act_init_policy(struct act_policy *pl,
		const enum act_action action, const enum act_sign sign)
{
	pl->action = action;
	pl->sign = sign;

	INIT_LIST_HEAD(&pl->sslv_conds);
	INIT_LIST_HEAD(&pl->oslv_conds);
	INIT_LIST_HEAD(&pl->srole_conds);
	INIT_LIST_HEAD(&pl->orole_conds);

	INIT_LIST_HEAD(&pl->list);
}
EXPORT_SYMBOL(act_init_policy);

/*
 * FIXME: handle overflow and rv = 0
 * FIXME: Have to ensure buffer size
 */
const char *act_policy_str(const struct act_policy *pl)
{
	static
		char buf[5000];

	const char *pt;
	const struct act_sec_lv_cond *slv_cond;
	const struct act_role_cond *role_cond;
	
	pt = act_sign_str(pl->sign);
	if (!pt)
		return NULL;

	sprintf(buf, "struct act_policy { sign = %s, sslv_conds: ", pt);

	list_for_each_entry(slv_cond, &pl->sslv_conds, list) {
		strcat(buf, act_cmp_str(slv_cond->cmp));
		strcat(buf, act_sec_lv_str(slv_cond->slv));
		strcat(buf, ",");
	}

	strcat(buf, "; srole_conds: ");
	list_for_each_entry(role_cond, &pl->srole_conds, list) {
		strcat(buf, act_cmp_str(role_cond->cmp));
		strcat(buf, act_role_str(role_cond->role));
		strcat(buf, ",");
	}

	strcat(buf, "; oslv_conds: ");
	list_for_each_entry(slv_cond, &pl->oslv_conds, list) {
		strcat(buf, act_cmp_str(slv_cond->cmp));
		strcat(buf, act_sec_lv_str(slv_cond->slv));
		strcat(buf, ",");
	}

	strcat(buf, "; orole_conds: ");
	list_for_each_entry(role_cond, &pl->orole_conds, list) {
		strcat(buf, act_cmp_str(role_cond->cmp));
		strcat(buf, act_role_str(role_cond->role));
		strcat(buf, ",");
	}
	strcat(buf, ";");

	return buf;
}
EXPORT_SYMBOL(act_policy_str);

void act_add_policy(struct act_policy *pl)
{
	list_add(&pl->list, &act_policies);
}
EXPORT_SYMBOL(act_add_policy);

static
int act_sec_lv_test_cond(const struct act_sec_lv_cond *cond,
		const enum act_sec_lv slv)
{
	switch (cond->cmp)
	{
	case ACT_EQUAL:
		return slv == cond->slv ? 1 : 0;
	case ACT_LESS_EQUAL:
		return slv <= cond->slv ? 1 : 0;
	case ACT_GREATER_EQUAL:
		return slv >= cond->slv ? 1 : 0;
	default:
		return -EINVAL;
	}
}

static
int act_role_test_cond(const struct act_role_cond *cond,
		const enum act_role role)
{
	switch (cond->cmp)
	{
	case ACT_EQUAL:
		return role == cond->role ? 1 : 0;
	case ACT_LESS_EQUAL:
		return role <= cond->role ? 1 : 0;
	case ACT_GREATER_EQUAL:
		return role >= cond->role ? 1 : 0;
	default:
		return -EINVAL;
	}
}

/*
 * FIXME: return value if (!rv)
 */
static
int act_sec_lv_test_conds(const struct list_head *conds,
		const enum act_sec_lv slv)
{
	const struct act_sec_lv_cond *cond;
	int rv;

	if (list_empty(conds))
		return !0;

	list_for_each_entry(cond, conds, list) {
		rv = act_sec_lv_test_cond(cond, slv);
		if (rv)
			return !0;
	}
	return 0;
}

static
int act_role_test_conds(const struct list_head *conds,
		const enum act_role role)
{
	const struct act_role_cond *cond;
	int rv;

	if (list_empty(conds))
		return !0;

	list_for_each_entry(cond, conds, list) {
		rv = act_role_test_cond(cond, role);
		if (rv)
			return !0;
	}
	return 0;
}

int act_policy_check(struct act_policy *pl,
		const struct act_subj_ctx *sav, const struct act_obj_ctx *oav,
		enum act_action action)
{
	int rv;

	if (action != pl->action)
		return ACT_NOT_APPLICABLE;

	rv = act_sec_lv_test_conds(&pl->sslv_conds, sav->sslv);
	if (!rv)
		return ACT_NOT_APPLICABLE;

	rv = act_role_test_conds(&pl->srole_conds, sav->srole);
	if (!rv)
		return ACT_NOT_APPLICABLE;

	rv = act_sec_lv_test_conds(&pl->oslv_conds, oav->oslv);
	if (!rv)
		return ACT_NOT_APPLICABLE;

	rv = act_role_test_conds(&pl->orole_conds, oav->orole);
	if (!rv)
		return ACT_NOT_APPLICABLE;

	return pl->sign;
}
EXPORT_SYMBOL(act_policy_check);
