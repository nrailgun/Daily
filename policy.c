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

#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "act.h"
#include "policy.h"

LIST_HEAD(act_policies);

const char *
act_sign_str(const act_sign_t sign)
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

const char *
act_action_str(const act_action_t act)
{
	if (act < ACT_ACTION_BPRM_SET_CREDS || act > ACT_ACTION_FILE_OPEN)
		return "UNKNOWN_ACTION";

	return "Known Action";
}

const char *
act_cmp_str(const act_cmp_t cmp)
{
	switch (cmp)
	{
	case ACT_CMP_EQUAL:
		return "=";

	case ACT_CMP_LESS:
		return "<";

	case ACT_CMP_GREATER:
		return ">";

	case ACT_CMP_IN:
		return "in";

	default:
		return NULL;
	}
}

act_cond_t *act_new_cond(void)
{
	act_cond_t *pt;
	
	pt = kmalloc(sizeof(act_cond_t), GFP_KERNEL);
	if (!pt)
		return NULL;
	memset(pt, 0, sizeof(*pt));

	pt->cond_type = ACT_COND_TYPE_SINGLE;

	return pt;
}
