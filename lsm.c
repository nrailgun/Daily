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
 * Copyright (C) Junyu wu, shibuyanorailgun@gmail.com, 2014.
 */

#include <linux/binfmts.h>
#include <linux/dcache.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/security.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/xattr.h>

#include "act.h"
#include "parse.h"
#include "policy.h"

static
int act_bprm_set_creds(struct linux_binprm *bprm)
{
	struct dentry *dent;
	const struct inode_operations *iop;
	struct act_subj_ctx *ctx;
	int rv;
	char buf[ACT_XATTR_LEN + 1];

#ifdef CONFIG_ACT_VERB_INFO
	ACT_INFO("binprm %s set creds.", bprm->filename);
#endif

#ifdef CONFIG_ACT_DEBUG_INFO
	if (!bprm->cred->security) {
		panic("should have bpm->cred->security.");
	}
#endif

	if (bprm->cred_prepared)
		return 0;

	dent = bprm->file->f_dentry;
	iop = bprm->file->f_inode->i_op;
	ctx = bprm->cred->security;

	if (iop->getxattr) {
		rv = iop->getxattr(dent, XATTR_SECURITY_PREFIX "sslv",
				buf, ACT_XATTR_LEN);
		if (rv < 0)
		{
#ifdef CONFIG_ACT_DEBUG_INFO
			ACT_INFO("getxattr no value, %d returned.", rv);
#endif
			return 0;
		}
		buf[rv] = 0;

#ifdef CONFIG_ACT_DEBUG_INFO
		ACT_INFO("%s getxattr xattr %s.", bprm->filename, buf);
#endif
		rv = act_str_sec_lv(buf, &ctx->sslv);
		if (rv == -EINVAL) {
			ACT_WARN("%s act_str_sec_lv parse failed.", buf);
			return !0;
		}

		/* TODO security role */
	}
	else {
		ACT_INFO("%s has no getxattr operation.", bprm->filename);
	}
	return 0;
}

static
int act_file_permission(struct file *filp, int mask)
{
	struct act_subj_ctx *ctx = current->cred->security;
	struct act_obj_ctx *octx = filp->f_security;
	struct act_policy *pl;
	int rv, check = -EACCES;
#if 1
	if (strcmp(filp->f_dentry->d_iname, "testf")) {
		return 0;
	}
#endif

#ifdef CONFIG_ACT_DEBUG_INFO
	ACT_INFO("permission checking...");

	ACT_INFO("file_permission current sec_lv %s and role %s.",
			act_sec_lv_str(ctx->sslv), act_role_str(ctx->srole));

	ACT_INFO("file_permission file sec_lv %s and role %s.",
			act_sec_lv_str(octx->oslv), act_role_str(octx->orole));
#endif

	list_for_each_entry(pl, &act_policies, list) {
		rv = act_policy_check(pl, ctx, octx, ACT_ACTION_FILE_PERMISSION);
		switch (rv)
		{
		case ACT_NOT_APPLICABLE:
			ACT_INFO("not applicable");
			continue;

		case ACT_DENY:
			ACT_INFO("deny");
			return -EACCES;

		case ACT_ALLOW:
			ACT_INFO("allow");
			check = 0;
			continue;

#ifdef CONFIG_ACT_DEBUG_INFO
		default:
			panic("panic, this really should not be");
#endif
		}
	}

	return check;
}

static
int act_file_alloc_security(struct file *filp)
{
	struct act_obj_ctx *ctx;

	ctx = kmalloc(sizeof(struct act_obj_ctx), GFP_KERNEL);
	if (!ctx) {
		return -ENOMEM;
	}
	act_init_obj_ctx(ctx, ACT_TRIVIAL, ACT_USER);
	filp->f_security = ctx;

	return 0;
}

static
void act_file_free_security(struct file *filp)
{
	void *pt = filp->f_security;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_INFO("file_free_security %p", pt);
#endif
	if (pt) {
		kfree(pt);
		filp->f_security = NULL;
	}
}

int act_file_open(struct file *filp, const struct cred *cred)
{
	struct act_subj_ctx *ctx;
	struct act_obj_ctx *octx;
	const struct inode_operations *iop;
	int rv;
	char buf[ACT_XATTR_LEN + 1];

	ctx = current->cred->security;
#ifdef CONFIG_ACT_DEBUG_INFO
	if (!ctx) {
		ACT_ERROR("should have cred->security.");
		return 0;
	}
#endif

	octx = filp->f_security;
#ifdef CONFIG_ACT_DEBUG_INFO
	if (!octx) {
		ACT_INFO("should have filp->f_security.");
		return 0;
	}
#endif

	if (filp->f_inode)
	{
		if (!(iop = filp->f_inode->i_op)) {
#ifdef CONFIG_ACT_DEBUG_INFO
			ACT_INFO("has no inode_operations.");
#endif
			return 0;
		}
	}
	else {
#ifdef CONFIG_ACT_DEBUG_INFO
		ACT_INFO("no f_inode for filp.");
#endif
		return 0;
	}

	if (iop->getxattr) {
		rv = iop->getxattr(filp->f_dentry, XATTR_SECURITY_PREFIX "oslv",
				buf, ACT_XATTR_LEN);

		if (rv < 0) { // TODO no value error
#ifdef CONFIG_ACT_DEBUG_INFO
			ACT_INFO("no attr, return value %d.", rv);
#endif
			return 0;
		}
		buf[rv] = 0;

		rv = act_str_sec_lv(buf, &octx->oslv);
		if (rv < 0) {
#ifdef CONFIG_ACT_DEBUG_INFO
			ACT_INFO("failed to parse object security level.");
#endif
			return !0;
		}
	}
#ifdef CONFIG_ACT_DEBUG_INFO
	else {
		ACT_INFO("no getxattr");
	}
#endif

#ifdef CONFIG_ACT_DEBUG_INFO
	ACT_INFO("file_open current sec_lv %s and role %s.",
			act_sec_lv_str(ctx->sslv), act_role_str(ctx->srole));

	ACT_INFO("file_open file sec_lv %s and role %s.",
			act_sec_lv_str(octx->oslv), act_role_str(octx->orole));
#endif
	return 0;
}

int act_file_lock(struct file *filp, unsigned int cmd)
{
	return 0;
}

static
int act_cred_prepare(struct cred *new, const struct cred *old, gfp_t gfp)
{
	struct act_subj_ctx *ctx;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_INFO("cred_prepare");
#endif
	ctx = kmalloc(sizeof(struct act_subj_ctx), GFP_KERNEL);
	new->security = ctx;

	if (!ctx)
		return -ENOMEM;
	act_init_subj_ctx(ctx, ACT_TRIVIAL, ACT_USER);

	return 0;
}

static
void act_cred_free(struct cred *cr)
{
#ifdef CONFIG_ACT_VERB_INFO
	ACT_INFO("cred_free");
#endif
	kfree(cr->security);
	cr->security = NULL;
}

#ifndef MODULE

static
struct security_operations ops =
{
	.name			= "act",

	.bprm_set_creds		= act_bprm_set_creds,

	.file_permission	= act_file_permission,
	.file_alloc_security	= act_file_alloc_security,
	.file_free_security	= act_file_free_security,
	.file_open		= act_file_open,
	.file_lock		= act_file_lock,

	.cred_prepare		= act_cred_prepare,
	.cred_free		= act_cred_free,
};

static
__init int act_module_init(void)
{
	int rv;
	struct act_subj_ctx *ctx;
	struct cred *cr;

	ACT_INFO("module initialzing...");

	if (!security_module_enable(&ops))
		return 0;

	ctx = kmalloc(sizeof(struct act_subj_ctx), GFP_KERNEL);
	if (!ctx) {
		ACT_ERROR("failed to alloc context.");
		return !0;
	}
	act_init_subj_ctx(ctx, ACT_TRIVIAL, ACT_USER);

	cr = (struct cred *) current->cred;
	cr->security = ctx;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_INFO("init task security %p", ctx);
#endif

	rv = register_security(&ops);
	if (rv) {
		ACT_ERROR("failed to register security_operations.");
		return rv;
	}
	ACT_INFO("register_security success.");

	return 0;
}

security_initcall(act_module_init);

#endif /* ifdef MODULE */
