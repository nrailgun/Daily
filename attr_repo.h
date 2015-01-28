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

#include <linux/list.h>

#include "attr_repo_ctx.h"

enum act_attr_type {
	ACT_ATTR_TYPE_INT, ACT_ATTR_TYPE_INTS,
	ACT_ATTR_TYPE_STR, ACT_ATTR_TYPE_STRS
};

struct act_attr {
	char *key;
	enum act_attr_type type;
	union {
		int intval;
		int *intvals;
		char *strval;
		char **strvals;
	};
	int nvals;
	struct list_head list;
	struct act_attr_ctx *ctx;
};

/*
 * Attributes certificate.
 */
struct act_cert {
	struct list_head attrs;
	u_char signature[256];
	struct act_cert_ctx *ctx;
};

/*
 * Get subject (process) attributes certificate.
 *
 * @bprm: Linux binary program to be `exec`ed.
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
