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

#ifndef __LINUX_ACT_ATTR_REPO_H
#define __LINUX_ACT_ATTR_REPO_H

#include <linux/binfmts.h>
#include <linux/fs.h>
#include <linux/list.h>

#include "act.h"
#include "attr_repo_ctx.h"

typedef enum act_attr_type {
	ACT_ATTR_TYPE_INT, ACT_ATTR_TYPE_INTS,
	ACT_ATTR_TYPE_STR, ACT_ATTR_TYPE_STRS
} act_attr_type_t;

typedef enum act_owner {
	ACT_OWNER_UNDEF, ACT_OWNER_SUBJ, ACT_OWNER_OBJ, ACT_OWNER_ENV
} act_owner_t;

typedef struct act_attr {
	char *key;
	act_attr_type_t type;
	union {
		int intval;
		char *strval;
		struct {
			union {
				int *intvals;
				char **strvals;
			};
			int nvals;
		};
	};
	struct list_head list;
	struct act_attr_ctx *ctx;
} act_attr_t;

typedef struct act_cert {
	act_owner_t owner;
	struct list_head attrs;
	struct act_cert_ctx *ctx;
	u_char signature[256];
} act_cert_t;

/*
 * Get subject (process) attributes certificate.
 *
 * @bprm: Binary program to be `exec`ed, NULL on fork.
 *
 * @return: Subject (process) attributes certificate, NULL on failure.
 */
struct act_cert *
act_subj_attrs(const struct linux_binprm *bprm);

/*
 * Destroy subject attributes certificate.
 */
void
act_subj_attrs_destroy(struct act_cert *cert);

/*
 * Get file object attributes certificate.
 *
 * @return: file object attributes certificate, NULL on failure.
 */
struct act_cert *
act_obj_file_attrs(const struct file *filp);

/*
 * Destroy object attributes certificate.
 */
void
act_obj_file_attrs_destroy(struct act_cert *cert);

/*
 * Get inode object attributes certificate.
 *
 * @return: inode object attributes certificate, NULL on failure.
 */
struct act_cert *
act_obj_inode_attrs(const struct inode *inodp);

/*
 * Destroy object attributes certificate.
 */
void
act_obj_inode_attrs_destroy(struct act_cert *cert);

/*
 * Verify the integrity of given attributes certificate. 
 *
 * @cert: Certificate given.
 *
 * @return: 1 on success.
 */
int
act_cert_verify(const struct act_cert *cert);

#endif /* end of include guard: __LINUX_ACT_ATTR_REPO_H */
