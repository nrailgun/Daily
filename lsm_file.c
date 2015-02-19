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

#include <linux/fs.h>
#include <linux/list.h>

#include "act.h"
#include "attr_repo.h"
#include "lsm.h"
#include "lsm_file.h"
#include "policy.h"

int act_file_permission(struct file *filp, int mask)
{
	act_cert_t *subj, *obj;
	struct list_head *pls, *l;
	act_policy_t *p;
	act_sign_t sign;
#if 1
	if (strcmp(filp->f_dentry->d_iname, "testf")) {
		return 0;
	}
#endif
	subj = current->cred->security;
	obj = filp->f_security;

	if (!subj && !obj)
		return 0;

	pls = act_policy_list(ACT_ACTION_FILE_PERMISSION);
	list_for_each(l, pls)
	{
		p = list_entry(l, act_policy_t, list);
		sign = act_policy_check(p, subj, obj);

		switch (sign)
		{
		case ACT_SIGN_DENY:
			return -EACCES;

		case ACT_SIGN_ALLOW:
			continue;

		case ACT_SIGN_NOT_APPLICABLE:
			continue;
		}
	}
	return 0;
}

int act_file_alloc_security(struct file *filp)
{
	act_cert_t *ctx;

	ctx = act_obj_file_attrs(filp);
	filp->f_security = (void *) ctx;

	return 0;
}

void act_file_free_security(struct file *filp)
{
	act_cert_t *pt = (act_cert_t *) filp->f_security;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_INFO("file_free_security %p", pt);
#endif
	if (pt) {
		act_obj_file_attrs_destroy(pt);
		filp->f_security = NULL;
	}
}
