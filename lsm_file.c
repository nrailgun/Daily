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
#include <linux/string.h>

#include "act.h"
#include "attr_repo.h"
#include "attr_repo_help.h"
#include "lsm.h"
#include "lsm_file.h"
#include "policy.h"

int act_file_permission(struct file *filp, int mask)
{
	act_cert_t *subj, *obj;
	struct list_head *pls, *l;
	act_policy_t *p;
	act_sign_t sign;
	char buf[500];
#if 1
	int rv;

	rv = strcmp("testf", filp->f_dentry->d_iname);
	rv = rv && strcmp("testf-2", filp->f_dentry->d_iname);
	if (rv)
		return 0;
#endif
	subj = current->cred->security;
	if (!subj) {
		ACT_Warn("file_permisson subj cert null");
		return -EACCES;
	}

	rv = act_cert_str(subj, buf, 500);
	if (0 < rv)
		ACT_Info("file_permisson subject: %s", buf);
	else
		ACT_Info("file_permisson cert_str failed %d", rv);

	obj = filp->f_security;
	if (!obj) {
		ACT_Warn("file_permisson obj cert null");
		return -EACCES;
	}

	rv = act_cert_str(obj, buf, 500);
	if (0 < rv)
		ACT_Info("file_permisson object: %s", buf);
	else
		ACT_Info("file_permisson cert_str failed %d", rv);

	pls = act_policy_list(ACT_ACTION_FILE_PERMISSION);
	list_for_each(l, pls)
	{
		p = list_entry(l, act_policy_t, list);
		act_policy_str(p, buf, 500);
		ACT_Info("%s", buf);

		sign = act_policy_check(p, subj, obj);
		ACT_Info("%s", act_sign_str(sign));

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

#ifdef CONFIG_ACT_VERB_INFO
	ACT_Info("file_alloc_security %p", ctx);
#endif
	return 0;
}

void act_file_free_security(struct file *filp)
{
	act_cert_t *ctx = (act_cert_t *) filp->f_security;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_Info("file_free_security %p", ctx);
#endif
	if (ctx) {
		act_obj_file_attrs_destroy(ctx);
		filp->f_security = NULL;
	}
}
