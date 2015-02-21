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

#ifndef __LINUX_ACT_LSM_FILE_H
#define __LINUX_ACT_LSM_FILE_H

#include <linux/fs.h>

#include "act.h"

int
act_file_alloc_security(struct file *);

void
act_file_free_security(struct file *);

int
act_file_open(struct file *, const struct cred *);

int
act_file_permission(struct file *, int);

#endif /* end of include guard: __LINUX_ACT_LSM_FILE_H */
