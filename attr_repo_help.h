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
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __LINUX_ATTR_REPO_HELP_H
#define __LINUX_ATTR_REPO_HELP_H

struct act_cert *act_cert_alloc(const act_owner_t owner);

void act_cert_add_attr(act_cert_t *cert,
		const act_attr_type_t tp, char *key, void *v);

#endif /* end of include guard: __LINUX_ATTR_REPO_HELP_H */
