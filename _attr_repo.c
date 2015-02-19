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

#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "act.h"
#include "attr_repo.h"

#ifdef CONFIG_ACT_TEST_ATTR_REPO_EMPTY

static
struct act_cert *act_cert_alloc(void)
{
	struct act_cert *cert;

	cert = kmalloc(sizeof(*cert), GFP_KERNEL);
	if (cert) {
		cert->owner = ACT_OWNER_UNDEF;
		INIT_LIST_HEAD(&cert->attrs);
		cert->ctx = NULL;
	}
	return cert;
}

struct act_cert *
act_subj_attrs(const struct linux_binprm *bprm)
{
	struct act_cert *cert;
	cert = act_cert_alloc();
	cert->owner = ACT_OWNER_SUBJ;

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
	cert = act_cert_alloc();
	cert->owner = ACT_OWNER_OBJ;

	return cert;
}

void
act_obj_file_attrs_destroy(struct act_cert *cert)
{
	if (cert) {
		kfree(cert);
	}
}

#elif defined CONFIG_ACT_TEST_ATTR_REPO_NULL

struct act_cert *
act_subj_attrs(const struct linux_binprm *bprm)
{
	return NULL;
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
	return NULL;
}

void
act_obj_file_attrs_destroy(struct act_cert *cert)
{
	if (cert) {
		kfree(cert);
	}
}

#endif

int
act_cert_verify(const struct act_cert *cert)
{
	return !0;
}
