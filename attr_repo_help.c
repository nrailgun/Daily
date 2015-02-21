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
#include <linux/ctype.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/xattr.h>

#include "Asserts.h"
#include "act.h"
#include "attr_repo.h"
#include "attr_repo_help.h"

const
char *act_owner_str(const act_owner_t owner)
{
	switch (owner)
	{
	case ACT_OWNER_UNDEF:
		return "Undefined";

	case ACT_OWNER_SUBJ:
		return "SUBJECT";

	case ACT_OWNER_OBJ:
		return "OBJECT";

	case ACT_OWNER_ENV:
		return "ENVIRONMENT";

	default:
		return NULL;
	}
}

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

int act_cert_str(const act_cert_t *cert, char buf[], const size_t sz)
{
	int i;
	struct list_head *l;
	act_attr_t *a;

	strncpy(buf, "{ ", sz);
	i = strlen(buf);

	list_for_each(l, &cert->attrs)
	{
		a = list_entry(l, act_attr_t, list);
		switch (a->type)
		{
		case ACT_ATTR_TYPE_INT:
			if (i >= sz)
				return -E2BIG;
			snprintf(buf + i, sz - i, "%s = %d; ", a->key, a->intval);
			i = strlen(buf);
			break;

		case ACT_ATTR_TYPE_STR:
			if (i >= sz)
				return -E2BIG;
			snprintf(buf + i, sz - i, "%s = '%s'; ", a->key, a->strval);
			i = strlen(buf);
			break;

		default:
			return -EPERM;
		}
	}

	if (i >= sz)
		return -E2BIG;
	snprintf(buf + i, sz - i, "}");

	return ++i;
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

#ifdef CONFIG_ACT_TEST

act_attr_type_t act_xattr_parse_val(const char xattr[], void **vp)
{
	act_attr_type_t tp;
	int i, j, iv;
	char *s;

	if (xattr[0] == '\'')
		tp = ACT_ATTR_TYPE_STR;
	else {
		tp = ACT_ATTR_TYPE_INT;
		ACT_Assert(isdigit(*xattr));
	}

	switch (tp)
	{
	case ACT_ATTR_TYPE_STR:
		s = kmalloc(100, GFP_KERNEL);
		i = 1, j = 0;
		while (xattr[i] != '\'') {
			s[j++] = xattr[i++];
		}
		s[j] = 0;
		*vp = s;
		break;

	case ACT_ATTR_TYPE_INT:
		i = 0, iv = 0;
		while (xattr[i] != ';') {
			iv *= 10;
			iv += xattr[i++] - '0';
		}
		*vp = (void *) iv;
		break;

	default:
		ACT_Assert(0);
	}
	return tp;
}

act_cert_t *act_xattr_parse(const act_owner_t owner,
			    const char xattr[], const size_t sz)
{
	act_cert_t *cert;
	int i, j;
	char *nbuf;
	act_attr_type_t tp;
	void *v;

	cert = act_cert_alloc(owner);
	if (!cert)
		return NULL;

	for (i = 0; i < sz; ) {
		nbuf = kmalloc(50, GFP_KERNEL);
		for (j = 0; xattr[i + j] != '='; j++)
			nbuf[j] = xattr[i + j];
		nbuf[j] = 0;

		i += ++j;
		tp = act_xattr_parse_val(xattr + i, &v);
		act_cert_add_attr(cert, tp, nbuf, v);

		for ( ; xattr[i++] != ';'; ) ;
	}
	return cert;
}

#endif /* CONFIG_ACT_TEST */

#ifdef CONFIG_ACT_TEST_LSM

struct act_cert *
act_subj_attrs(const struct linux_binprm *bprm)
{
	struct act_cert *cert = NULL;

#ifdef __KERNEL__
	struct file *filp;
	struct dentry *dent;
	const struct inode_operations *iop;
	int rv;
	char buf[500];

	if (!bprm)
		return NULL;

	filp = bprm->file;
	dent = filp->f_dentry;
	iop = filp->f_inode->i_op;

	if (iop->getxattr) {
		rv = iop->getxattr(dent, XATTR_SECURITY_PREFIX "attrs", buf, 500);
		if (rv < 0) {
			return act_cert_alloc(ACT_OWNER_SUBJ);
		}
		buf[rv] = 0;
#ifdef CONFIG_ACT_DEBUG_INFO
		ACT_Info("%s getxattr xattr %s", bprm->filename, buf);
#endif
		cert = act_xattr_parse(ACT_OWNER_SUBJ, buf, rv);
	}
#else /* __KERNEL__ */

	cert = act_cert_alloc(ACT_OWNER_SUBJ);
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
	struct act_cert *cert = NULL;

#ifdef __KERNEL__
	struct dentry *dent;
	struct inode *ino;
	const struct inode_operations *iop;
	int rv;
	char buf[500];

	if (!filp) {
		ACT_Warn("no file");
		return act_cert_alloc(ACT_OWNER_OBJ);
	}

	dent = filp->f_dentry;
	if (!dent) {
		ACT_Warn("no dentry");
		return act_cert_alloc(ACT_OWNER_OBJ);
	}

	ino = filp->f_inode;
	if (!ino) {
		ACT_Warn("no inode");
		return act_cert_alloc(ACT_OWNER_OBJ);
	}

	iop = ino->i_op;
	if (iop && iop->getxattr) {
		rv = iop->getxattr(dent, XATTR_SECURITY_PREFIX "attrs", buf, 500);
		if (rv < 0) {
			ACT_Warn("no xattr");
			return act_cert_alloc(ACT_OWNER_OBJ);
		}
		buf[rv] = 0;
		cert = act_xattr_parse(ACT_OWNER_OBJ, buf, rv);
	}
#endif
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

#endif /* ifdef CONFIG_ACT_TEST_LSM */
