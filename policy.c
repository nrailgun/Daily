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
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "Asserts.h"
#include "act.h"
#include "attr_repo.h"
#include "attr_repo_help.h"
#include "policy.h"

static
struct list_head policy_ls[ACT_ACTION_UNKNOWN];

const char *
act_sign_str(const act_sign_t sign)
{
	switch (sign)
	{
	case ACT_SIGN_NOT_APPLICABLE:
		return "NOT_APPLICABLE";

	case ACT_SIGN_DENY:
		return "DENY";

	case ACT_SIGN_ALLOW:
		return "ALLOW";

	default:
		return NULL;
	}
}

act_action_t act_str_action(const char s[], const size_t sz)
{
	static const char *pats[] = {
		"BPRM_SET_CREDS",
		"BPRM_CHECK_SECURITY",
		"BPRM_SECUREEXEC",

		"SB_COPY_DATA",
		"SB_REMOUNT",
		"SB_KERN_MOUNT",
		"SB_SHOW_OPTIONS",
		"SB_STATFS",
		"SB_MOUNT",
		"SB_UMOUNT",
		"SB_PIVOTROOT",
		"SB_SET_MNT_OPTS",
		"SB_CLONE_MNT_OPTS",
		"SB_PARSE_OPTS_STR",

#ifdef CONFIG_SECURITY_PATH
		"PATH_UNLINK",
		"PATH_MKDIR",
		"PATH_RMDIR",
		"PATH_MKNOD",
		"PATH_TRUNCATE",
		"PATH_SYMLINK",
		"PATH_LINK",
		"PATH_RENAME",
		"PATH_CHMOD",
		"PATH_CHOWN",
		"PATH_CHROOT",
#endif

		"INODE_CREATE",
		"INODE_LINK",
		"INODE_UNLINK",
		"INODE_SYMLINK",
		"INODE_MKDIR",
		"INODE_RMDIR",
		"INODE_MKNOD",
		"INODE_RENAME",
		"INODE_READLINK",
		"INODE_FOLLOW_LINK",
		"INODE_PERMISSION",
		"INODE_SETATTR",
		"INODE_GETATTR",
		"INODE_SETXATTR",
		"INODE_GETXATTR",
		"INODE_LISTXATTR",
		"INODE_REMOVEXATTR",
		"INODE_NEED_KILLPRIV",
		"INODE_KILLPRIV",
		"INODE_GETSECURITY",
		"INODE_SETSECURITY",
		"INODE_LISTSECURITY",

		"FILE_PERMISSION",
		"FILE_IOCTL",
		"MMAP_ADDR",
		"MMAP_FILE",
		"FILE_MPROTECT",
		"FILE_LOCK",
		"FILE_FCNTL",
		"FILE_SET_FOWNER",
		"FILE_SEND_SIGIOTASK",
		"FILE_RECEIVE",
		"FILE_OPEN",
	};

	int i;

	for (i = 0; i < ARRAY_SIZE(pats); ++i)
	{
		if (!strncmp(s, pats[i], sz)) {
			return (act_action_t) i;
		}
	}
	return ACT_ACTION_UNKNOWN;
}

const char *
act_action_str(const act_action_t act)
{
	switch (act)
	{
	case ACT_ACTION_BPRM_SET_CREDS:
		return "ACT_ACTION_BPRM_SET_CREDS";

	case ACT_ACTION_BPRM_CHECK_SECURITY:
		return "ACT_ACTION_BPRM_CHECK_SECURITY";

	case ACT_ACTION_BPRM_SECUREEXEC:
		return "ACT_ACTION_BPRM_SECUREEXEC";

	case ACT_ACTION_SB_COPY_DATA:
		return "ACT_ACTION_SB_COPY_DATA";

	case ACT_ACTION_SB_REMOUNT:
		return "ACT_ACTION_SB_REMOUNT";

	case ACT_ACTION_SB_KERN_MOUNT:
		return "ACT_ACTION_SB_KERN_MOUNT";

	case ACT_ACTION_SB_SHOW_OPTIONS:
		return "ACT_ACTION_SB_SHOW_OPTIONS";

	case ACT_ACTION_SB_STATFS:
		return "ACT_ACTION_SB_STATFS";

	case ACT_ACTION_SB_MOUNT:
		return "ACT_ACTION_SB_MOUNT";

	case ACT_ACTION_SB_UMOUNT:
		return "ACT_ACTION_SB_UMOUNT";

	case ACT_ACTION_SB_PIVOTROOT:
		return "ACT_ACTION_SB_PIVOTROOT";

	case ACT_ACTION_SB_SET_MNT_OPTS:
		return "ACT_ACTION_SB_SET_MNT_OPTS";

	case ACT_ACTION_SB_CLONE_MNT_OPTS:
		return "ACT_ACTION_SB_CLONE_MNT_OPTS";

	case ACT_ACTION_SB_PARSE_OPTS_STR:
		return "ACT_ACTION_SB_PARSE_OPTS_STR";

#ifdef CONFIG_SECURITY_PATH

	case ACT_ACTION_PATH_UNLINK:
		return "ACT_ACTION_PATH_UNLINK";

	case ACT_ACTION_PATH_MKDIR:
		return "ACT_ACTION_PATH_MKDIR";

	case ACT_ACTION_PATH_RMDIR:
		return "ACT_ACTION_PATH_RMDIR";

	case ACT_ACTION_PATH_MKNOD:
		return "ACT_ACTION_PATH_MKNOD";

	case ACT_ACTION_PATH_TRUNCATE:
		return "ACT_ACTION_PATH_TRUNCATE";

	case ACT_ACTION_PATH_SYMLINK:
		return "ACT_ACTION_PATH_SYMLINK";

	case ACT_ACTION_PATH_LINK:
		return "ACT_ACTION_PATH_LINK";

	case ACT_ACTION_PATH_RENAME:
		return "ACT_ACTION_PATH_RENAME";

	case ACT_ACTION_PATH_CHMOD:
		return "ACT_ACTION_PATH_CHMOD";

	case ACT_ACTION_PATH_CHOWN:
		return "ACT_ACTION_PATH_CHOWN";

	case ACT_ACTION_PATH_CHROOT:
		return "ACT_ACTION_PATH_CHROOT";
#endif

	case ACT_ACTION_INODE_CREATE:
		return "ACT_ACTION_INODE_CREATE";

	case ACT_ACTION_INODE_LINK:
		return "ACT_ACTION_INODE_LINK";

	case ACT_ACTION_INODE_UNLINK:
		return "ACT_ACTION_INODE_UNLINK";

	case ACT_ACTION_INODE_SYMLINK:
		return "ACT_ACTION_INODE_SYMLINK";

	case ACT_ACTION_INODE_MKDIR:
		return "ACT_ACTION_INODE_MKDIR";

	case ACT_ACTION_INODE_RMDIR:
		return "ACT_ACTION_INODE_RMDIR";

	case ACT_ACTION_INODE_MKNOD:
		return "ACT_ACTION_INODE_MKNOD";

	case ACT_ACTION_INODE_RENAME:
		return "ACT_ACTION_INODE_RENAME";

	case ACT_ACTION_INODE_READLINK:
		return "ACT_ACTION_INODE_READLINK";

	case ACT_ACTION_INODE_FOLLOW_LINK:
		return "ACT_ACTION_INODE_FOLLOW_LINK";

	case ACT_ACTION_INODE_PERMISSION:
		return "ACT_ACTION_INODE_PERMISSION";

	case ACT_ACTION_INODE_SETATTR:
		return "ACT_ACTION_INODE_SETATTR";

	case ACT_ACTION_INODE_GETATTR:
		return "ACT_ACTION_INODE_GETATTR";

	case ACT_ACTION_INODE_SETXATTR:
		return "ACT_ACTION_INODE_SETXATTR";

	case ACT_ACTION_INODE_GETXATTR:
		return "ACT_ACTION_INODE_GETXATTR";

	case ACT_ACTION_INODE_LISTXATTR:
		return "ACT_ACTION_INODE_LISTXATTR";

	case ACT_ACTION_INODE_REMOVEXATTR:
		return "ACT_ACTION_INODE_REMOVEXATTR";

	case ACT_ACTION_INODE_NEED_KILLPRIV:
		return "ACT_ACTION_INODE_NEED_KILLPRIV";

	case ACT_ACTION_INODE_KILLPRIV:
		return "ACT_ACTION_INODE_KILLPRIV";

	case ACT_ACTION_INODE_GETSECURITY:
		return "ACT_ACTION_INODE_GETSECURITY";

	case ACT_ACTION_INODE_SETSECURITY:
		return "ACT_ACTION_INODE_SETSECURITY";

	case ACT_ACTION_INODE_LISTSECURITY:
		return "ACT_ACTION_INODE_LISTSECURITY";

	case ACT_ACTION_FILE_PERMISSION:
		return "ACT_ACTION_FILE_PERMISSION";

	case ACT_ACTION_FILE_IOCTL:
		return "ACT_ACTION_FILE_IOCTL";

	case ACT_ACTION_MMAP_ADDR:
		return "ACT_ACTION_MMAP_ADDR";

	case ACT_ACTION_MMAP_FILE:
		return "ACT_ACTION_MMAP_FILE";

	case ACT_ACTION_FILE_MPROTECT:
		return "ACT_ACTION_FILE_MPROTECT";

	case ACT_ACTION_FILE_LOCK:
		return "ACT_ACTION_FILE_LOCK";

	case ACT_ACTION_FILE_FCNTL:
		return "ACT_ACTION_FILE_FCNTL";

	case ACT_ACTION_FILE_SET_FOWNER:
		return "ACT_ACTION_FILE_SET_FOWNER";

	case ACT_ACTION_FILE_SEND_SIGIOTASK:
		return "ACT_ACTION_FILE_SEND_SIGIOTASK";

	case ACT_ACTION_FILE_RECEIVE:
		return "ACT_ACTION_FILE_RECEIVE";

	case ACT_ACTION_FILE_OPEN:
		return "ACT_ACTION_FILE_OPEN";

	default:
		return "ACT_UNKNOWN_ACTION";
	}
}

const char *
act_cmp_str(const act_cmp_t cmp)
{
	switch (cmp)
	{
	case ACT_CMP_EQUAL:
		return "=";

	case ACT_CMP_LESS:
		return "<";

	case ACT_CMP_GREATER:
		return ">";

	case ACT_CMP_IN:
		return "~";

	default:
		return NULL;
	}
}

int act_empty_single_cond(act_single_cond_t *pt)
{
	return !memset(pt, 0, sizeof(*pt));
}

void act_destroy_single_cond(act_single_cond_t *cond)
{
	int i;

	kfree(cond->key);

	switch (cond->type)
	{
	case ACT_ATTR_TYPE_INT:
		break;

	case ACT_ATTR_TYPE_STR:
		kfree(cond->strval);
		break;

	case ACT_ATTR_TYPE_INTS:
		kfree(cond->intvals);
		break;

	case ACT_ATTR_TYPE_STRS:
		for (i = 0; i < cond->nvals; ++i)
			kfree(cond->strvals[i]);
		kfree(cond->strvals);
		break;

	default:
		ACT_Assert_exec("`act_destroy_single_cond` invalid cond type");
	}
}

int act_single_cond_str(
		const act_single_cond_t *cond, char *buf, const size_t sz)
{
	size_t i;
	int rv;
	const char *s;

	i = strlen(cond->key);
	if (i >= sz - 1)
		return -E2BIG;
	strcpy(buf, cond->key);
	
	s = act_cmp_str(cond->cmp);
	if (!s)
		return -EINVAL;
	strcat(buf + i, s);
	i += strlen(s);
	
	switch (cond->type)
	{
	case ACT_ATTR_TYPE_INT:
		rv = snprintf(buf + i, sz - i, "%d; ", cond->intval);
		if (rv < 0)
			return rv;
		return strlen(buf);

	case ACT_ATTR_TYPE_STR:
		rv = snprintf(buf + i, sz - i, "'%s'; ", cond->strval);
		if (rv < 0)
			return rv;
		return strlen(buf);

	case ACT_ATTR_TYPE_INTS:
		ACT_Assert_exec("Not implemented yet");
		return -EINVAL;

	case ACT_ATTR_TYPE_STRS:
		ACT_Assert_exec("Not implemented yet");
		return -EINVAL;

	default:
		return -EINVAL;
	}
}

const
char *act_cond_type_str(const act_cond_type_t tp)
{
	switch (tp)
	{
	case ACT_COND_TYPE_SINGLE:
		return "&";
		
	case ACT_COND_TYPE_OR:
		return "|";

	case ACT_COND_TYPE_AND:
		return "*";

	default:
		return NULL;
	}
}

act_cond_t *act_new_cond(void)
{
	act_cond_t *pt;
	
	pt = kmalloc(sizeof(act_cond_t), GFP_KERNEL);
	if (!pt)
		return NULL;
	memset(pt, 0, sizeof(*pt));

	return pt;
}

int act_init_cond_empty(act_cond_t *pt)
{
	memset(pt, 0, sizeof(*pt));
	pt->cond_type = ACT_COND_TYPE_AND;

	return 0;
}

void act_destroy_cond(act_cond_t *pt)
{
	int i;

	switch (pt->cond_type)
	{
	case ACT_COND_TYPE_SINGLE:
		act_destroy_single_cond(&pt->single_cond);
		break;

	case ACT_COND_TYPE_OR:
	case ACT_COND_TYPE_AND:
		for (i = 0; i < pt->nconds; ++i)
			act_destroy_cond(pt->conds[i]);
		break;

	default:
		ACT_Assert_exec("act_destroy_cond");
	}
}

int act_cond_str(const act_cond_t *cond, char buf[], const size_t sz)
{
	int i, j, rv;
	const char *lb = "{ ", *rb = "}; ";

	switch (cond->cond_type)
	{
	case ACT_COND_TYPE_SINGLE:
		rv = act_single_cond_str(&cond->single_cond, buf, sz);
		return rv;

	case ACT_COND_TYPE_OR:
		lb = "[ ";
		rb = "]; ";

	case ACT_COND_TYPE_AND:
		if (sz < 3)
			return -E2BIG;
		strcpy(buf, lb);

		for (i = 0, j = 2; i < cond->nconds; ++i) {
			rv = act_cond_str(cond->conds[i], buf + j, sz - j);
			if (rv < 0)
				return rv;
			j += rv;
		}
		
		if (sz - j < 4)
			return -E2BIG;
		strcpy(buf + j, rb);

		return j + 4;

	default:
		return -EINVAL;
	}
}

int act_init_policy_empty(act_policy_t *pl)
{
	memset(pl, 0, sizeof(*pl));
	act_init_cond_empty(&pl->cond);
	INIT_LIST_HEAD(&pl->list);

	return 0;
}

void act_destroy_policy(act_policy_t *pl)
{
	act_destroy_cond(&pl->cond);
}

int act_policy_str(const act_policy_t *pl, char *buf, const size_t sz)
{
	size_t i, j;

	snprintf(buf, sz, "%s %s IF ",
		 act_sign_str(pl->sign), act_action_str(pl->action));
	i = strlen(buf);

	j = act_cond_str(&pl->cond, buf + i, sz - i);
	if (j < 0)
		return j;

	return i + j;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int policy_check_single_int(
		const act_single_cond_t *sg, const act_attr_t *at)
{
	ACT_Assert(sg->type == ACT_ATTR_TYPE_INT);
	ACT_Assert(at->type == ACT_ATTR_TYPE_INT);

	switch (sg->cmp)
	{
	case ACT_CMP_EQUAL:
		return at->intval == sg->intval;

	case ACT_CMP_LESS:
		return at->intval < sg->intval;

	case ACT_CMP_GREATER:
		return at->intval > sg->intval;

	case ACT_CMP_IN:
	default:
		ACT_Assert(0);
	}
	return -EINVAL;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int policy_check_single_str(
		const act_single_cond_t *sg, const act_attr_t *at)
{
	ACT_Assert(sg->type == ACT_ATTR_TYPE_STR);
	ACT_Assert(at->type == ACT_ATTR_TYPE_STR);

	switch (sg->cmp)
	{
	case ACT_CMP_EQUAL:
		return strcmp(at->strval, sg->strval) == 0;

	case ACT_CMP_LESS:
		return strcmp(at->strval, sg->strval) < 0;

	case ACT_CMP_GREATER:
		return strcmp(at->strval, sg->strval) > 0;

	case ACT_CMP_IN:
	default:
		ACT_Assert(0);
	}
	return -EINVAL;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int policy_check_single(
		const act_single_cond_t *sg, const struct list_head *ats)
{
	act_attr_t *at;
	struct list_head *la;

	list_for_each(la, ats)
	{
		at = list_entry(la, act_attr_t, list);

		if (strcmp(sg->key, at->key))
			continue;

		if (sg->type != at->type)
			break;

		switch (sg->type)
		{
		case ACT_ATTR_TYPE_INT:
			return policy_check_single_int(sg, at);

		case ACT_ATTR_TYPE_STR:
			return policy_check_single_str(sg, at);

		case ACT_ATTR_TYPE_INTS:
		case ACT_ATTR_TYPE_STRS:
		default:
			ACT_Assert(0);
		}
	}
	return 0;
}

#ifndef CONFIG_ACT_TEST
static
#endif
int policy_check(const act_cond_t *cond,
		const struct list_head *sats, const struct list_head *oats)
{
	int i, rv = -EINVAL;
	const act_single_cond_t *sg;

	switch (cond->cond_type)
	{
	case ACT_COND_TYPE_OR:
		for (i = 0; i < cond->nconds; i++) {
			rv = policy_check(cond->conds[i], sats, oats);
			if (rv)
				return 1;
		}
		return 0;

	case ACT_COND_TYPE_AND:
		for (i = 0; i < cond->nconds; i++) {
			rv = policy_check(cond->conds[i], sats, oats);
			if (!rv)
				return 0;
		}
		return 1;

	case ACT_COND_TYPE_SINGLE:
		sg = &cond->single_cond;

		switch (sg->owner)
		{
		case ACT_OWNER_SUBJ:
			rv = policy_check_single(sg, sats);
			break;
		
		case ACT_OWNER_OBJ:
			rv = policy_check_single(sg, oats);
			break;

		default:
			ACT_Assert(0);
		}
		return rv ? 1 : 0;

	default:
		ACT_Assert(0);
	}
	return -EINVAL;
}

act_sign_t act_policy_check(const act_policy_t *pl,
		const act_cert_t *subj, const act_cert_t *obj)
{
	int rv;
	const act_cond_t *cond;
	const struct list_head *sa, *oa;

	rv = act_cert_verify(subj);
	if (!rv)
		return ACT_SIGN_DENY;

	rv = act_cert_verify(obj);
	if (!rv)
		return ACT_SIGN_DENY;

	cond = &pl->cond;
	sa = &subj->attrs;
	oa = &obj->attrs;

	if (policy_check(cond, sa, oa))
		return pl->sign;

	return ACT_SIGN_NOT_APPLICABLE;
}

void act_policy_list_init(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(policy_ls); ++i) {
		INIT_LIST_HEAD(&policy_ls[i]);
	}
}

int act_policy_list_add(act_policy_t *pl)
{
	int i;

	i = (int) pl->action;
	list_add(&pl->list, &policy_ls[i]);

	return 0;
}

struct list_head *act_policy_list(const act_action_t act)
{
	size_t i;
       
	i = (size_t) act;

	return &policy_ls[i];
}
