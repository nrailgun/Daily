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

#include <linux/binfmts.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "Asserts.h"
#include "act.h"
#include "attr_repo.h"
#include "attr_repo_help.h"

struct act_cert *act_cert_alloc(const act_owner_t owner)
{
	struct act_cert *cert;

	cert = kmalloc(sizeof(*cert), GFP_KERNEL);
	if (cert) {
		cert->owner = owner;
		INIT_LIST_HEAD(&cert->attrs);
		cert->ctx = NULL;
	}
	return cert;
}

void act_cert_add_attr(act_cert_t *cert,
		const act_attr_type_t tp, char *key, void *v)
{
	act_attr_t *at;

	at = kmalloc(sizeof(*at), GFP_KERNEL);

	at->type = tp;
	at->key = key;

	switch (tp)
	{
	case ACT_ATTR_TYPE_INT:
		at->intval = (int) v;
		break;

	case ACT_ATTR_TYPE_STR:
		at->strval = v;
		break;

	default:
		ACT_Assert(0);
	}

	INIT_LIST_HEAD(&at->list);
	list_add_tail(&at->list, &cert->attrs);
}

#ifdef CONFIG_ACT_TEST_LSM

struct act_cert *
act_subj_attrs(const struct linux_binprm *bprm)
{
	struct act_cert *cert = NULL;
#ifdef __KERNEL__
	const char *fname;

	if (!bprm)
		return NULL;
	fname = bprm->filename;

	if (!strcmp(fname, "/bin/cat")) {
		cert = act_cert_alloc(ACT_OWNER_SUBJ);
		act_cert_add_attr(cert, ACT_ATTR_TYPE_INT, "security", (void *) 2);
	}
	else if (!strcmp(fname, "/usr/bin/wc")) {
		cert = act_cert_alloc(ACT_OWNER_SUBJ);
	}
#endif
	return cert;
}

void
act_subj_attrs_destroy(struct act_cert *cert)
{
	if (cert) {
		kfree(cert);
	}
}

struct act_cert *
act_obj_file_attrs(const struct file *filp)
{
	struct act_cert *cert;

	cert = act_cert_alloc(ACT_OWNER_OBJ);

	return cert;
}

void
act_obj_file_attrs_destroy(struct act_cert *cert)
{
	if (cert) {
		kfree(cert);
	}
}

int
act_cert_verify(const struct act_cert *cert)
{
	return !0;
}

#endif
