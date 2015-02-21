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

#ifndef __LINUX_ACT_PARSE_H
#define __LINUX_ACT_PARSE_H

#include "act.h"
#include "policy.h"

#ifdef CONFIG_ACT_TEST

int tokenize(
	const char [], const size_t, char **);

int parse_int(
	const char [], const size_t, int *);

int parse_separator(
	const char [], const size_t);

int parse_single_cond(
	act_cond_t *, const char [], const size_t);

int parse_multi_conds(
	act_cond_t *, const char [], const size_t);

int parse_policy_action(
	act_policy_t *, const char [], const size_t);

int parse_policy_sign(
	act_policy_t *, const char [], const size_t);

#endif

int act_parse_policy(
	act_policy_t *, const char [], const size_t);

#endif /* end of include guard: __LINUX_ACT_PARSE_H */
