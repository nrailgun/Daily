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
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/security.h>

#include "act.h"
#include "attr_repo.h"
#include "lsm_file.h"
#include "policy.h"

static
int act_bprm_set_creds(struct linux_binprm *bprm)
{
	act_cert_t *ctx;

	if (bprm->cred_prepared)
		return 0;

	ctx = bprm->cred->security;
	if (ctx) {
		act_subj_attrs_destroy(ctx);
	}
#ifdef CONFIG_ACT_VERB_INFO
	else {
		ACT_Info("Proc has no attrs");
	}
#endif
	ctx = act_subj_attrs(bprm);
	bprm->cred->security = ctx;

#if 1 // def CONFIG_ACT_DEBUG_INFO
	ACT_Info("set_creds %s", bprm->filename);
	ACT_Info("set_creds bprm->cred->security %p", ctx);
#endif
	return 0;
}

static
int act_cred_prepare(struct cred *new, const struct cred *old, gfp_t gfp)
{
	act_cert_t *ctx;

	ctx = act_subj_attrs(NULL);
	new->security = ctx;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_Info("cred_prepare %p", ctx);
#endif
	return 0;
}

static
void act_cred_free(struct cred *cr)
{
#ifdef CONFIG_ACT_VERB_INFO
	ACT_Info("cred_free %p", cr->security);
#endif
	act_subj_attrs_destroy(cr->security);

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

	.cred_prepare		= act_cred_prepare,
	.cred_free		= act_cred_free,
};

static
__init int act_module_init(void)
{
	int rv;
	struct cred *cr;

	ACT_Info("module initialzing...");

	if (!security_module_enable(&ops))
		return 0;

	cr = (struct cred *) current->cred;
	cr->security = NULL;

#ifdef CONFIG_ACT_VERB_INFO
	ACT_Info("init task security %p", cr->security);
#endif

	rv = register_security(&ops);
	if (rv) {
		ACT_Error("failed to register security_operations.");
		return rv;
	}
	ACT_Info("register_security success.");

	act_policy_list_init();

	return 0;
}

security_initcall(act_module_init);

#endif /* ifdef MODULE */
