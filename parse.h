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

#ifndef __LINUX_ACT_PARSE_H
#define __LINUX_ACT_PARSE_H

#include "policy.h"

int act_str_sec_lv(const char *tok, enum act_sec_lv *slev);

int act_str_role(const char *tok, enum act_role *role);

int act_str_cmp(const char *tok, enum act_cmp *cmp);

int act_str_action(const char *tok, enum act_action *act);

int act_str_sign(const char *tok, enum act_sign *sign);

int act_str_separator(const char *tok, int *skip);

/*
 * Parse policy from @rule, and store the policy into @pl.
 *
 * @rule: Buffer for tokens separated by '\0'.
 * @rulesz: Size of @rule buffer.
 *
 * Return 0 on success, -EINVAL if the failed to parse @rule.
 */
int act_policy_parse(struct act_policy *pl,
		const char *rule, const size_t rulesz);

#endif /* end of include guard: __LINUX_ACT_PARSE_H */
