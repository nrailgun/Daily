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

#ifndef __LINUX_ACT_POLICY_H
#define __LINUX_ACT_POLICY_H

#include <linux/list.h>

#include "act.h"
#include "attr_repo.h"

typedef enum act_sign
{ 
	ACT_SIGN_NOT_APPLICABLE	= 0,
	ACT_SIGN_DENY		= 1,
	ACT_SIGN_ALLOW		= 2
} act_sign_t;

const char *
act_sign_str(const act_sign_t sign);

typedef enum act_action
{
	ACT_ACTION_BPRM_SET_CREDS = 0,
	ACT_ACTION_BPRM_CHECK_SECURITY,
	ACT_ACTION_BPRM_SECUREEXEC,

	ACT_ACTION_SB_COPY_DATA,
	ACT_ACTION_SB_REMOUNT,
	ACT_ACTION_SB_KERN_MOUNT,
	ACT_ACTION_SB_SHOW_OPTIONS,
	ACT_ACTION_SB_STATFS,
	ACT_ACTION_SB_MOUNT,
	ACT_ACTION_SB_UMOUNT,
	ACT_ACTION_SB_PIVOTROOT,
	ACT_ACTION_SB_SET_MNT_OPTS,
	ACT_ACTION_SB_CLONE_MNT_OPTS,
	ACT_ACTION_SB_PARSE_OPTS_STR,

#ifdef CONFIG_SECURITY_PATH
	ACT_ACTION_PATH_UNLINK,
	ACT_ACTION_PATH_MKDIR,
	ACT_ACTION_PATH_RMDIR,
	ACT_ACTION_PATH_MKNOD,
	ACT_ACTION_PATH_TRUNCATE,
	ACT_ACTION_PATH_SYMLINK,
	ACT_ACTION_PATH_LINK,
	ACT_ACTION_PATH_RENAME,
	ACT_ACTION_PATH_CHMOD,
	ACT_ACTION_PATH_CHOWN,
	ACT_ACTION_PATH_CHROOT,
#endif

	ACT_ACTION_INODE_CREATE,
	ACT_ACTION_INODE_LINK,
	ACT_ACTION_INODE_UNLINK,
	ACT_ACTION_INODE_SYMLINK,
	ACT_ACTION_INODE_MKDIR,
	ACT_ACTION_INODE_RMDIR,
	ACT_ACTION_INODE_MKNOD,
	ACT_ACTION_INODE_RENAME,
	ACT_ACTION_INODE_READLINK,
	ACT_ACTION_INODE_FOLLOW_LINK,
	ACT_ACTION_INODE_PERMISSION,
	ACT_ACTION_INODE_SETATTR,
	ACT_ACTION_INODE_GETATTR,
	ACT_ACTION_INODE_SETXATTR,
	ACT_ACTION_INODE_GETXATTR,
	ACT_ACTION_INODE_LISTXATTR,
	ACT_ACTION_INODE_REMOVEXATTR,
	ACT_ACTION_INODE_NEED_KILLPRIV,
	ACT_ACTION_INODE_KILLPRIV,
	ACT_ACTION_INODE_GETSECURITY,
	ACT_ACTION_INODE_SETSECURITY,
	ACT_ACTION_INODE_LISTSECURITY,

	ACT_ACTION_FILE_PERMISSION,
	ACT_ACTION_FILE_IOCTL,
	ACT_ACTION_MMAP_ADDR,
	ACT_ACTION_MMAP_FILE,
	ACT_ACTION_FILE_MPROTECT,
	ACT_ACTION_FILE_LOCK,
	ACT_ACTION_FILE_FCNTL,
	ACT_ACTION_FILE_SET_FOWNER,
	ACT_ACTION_FILE_SEND_SIGIOTASK,
	ACT_ACTION_FILE_RECEIVE,
	ACT_ACTION_FILE_OPEN,

	ACT_ACTION_UNKNOWN,
} act_action_t;

const char *
act_action_str(const act_action_t);

act_action_t act_str_action(const char [], const size_t);

typedef enum
{ 
	ACT_CMP_EQUAL,
	ACT_CMP_LESS,
	ACT_CMP_GREATER,
	ACT_CMP_IN
} act_cmp_t;

const char *
act_cmp_str(const act_cmp_t cmp);

typedef struct act_single_cond
{
	act_owner_t owner;
	act_attr_type_t type;
	char *key;
	act_cmp_t cmp;
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
} act_single_cond_t;

int act_empty_single_cond(act_single_cond_t *);

int act_init_single_cond(act_single_cond_t *, const act_attr_type_t,
	const char *, const act_cmp_t, const void *, const int);

void act_destroy_single_cond(act_single_cond_t *);

int act_single_cond_str(const act_single_cond_t *, char *, const size_t);

typedef enum act_cond_type
{
	ACT_COND_TYPE_SINGLE,
	ACT_COND_TYPE_OR,
	ACT_COND_TYPE_AND,
} act_cond_type_t;

const
char *act_cond_type_str(const act_cond_type_t);

#define ACT_COND_MAX_CHILDREN 4

typedef struct act_cond
{
	act_cond_type_t cond_type;
	union {
		act_single_cond_t single_cond;
		struct {
			struct act_cond *conds[ACT_COND_MAX_CHILDREN];
			int nconds;
		};
	};
} act_cond_t;

act_cond_t *act_new_cond(void);

int act_init_cond_empty(act_cond_t *);

void act_destroy_cond(act_cond_t *);

int act_cond_str(const act_cond_t *, char [], const size_t);

typedef struct act_policy
{
	act_action_t		action;
	act_sign_t		sign;
	act_cond_t		cond;
	struct list_head	list;
} act_policy_t;

int act_init_policy_empty(act_policy_t *);

void act_destroy_policy(act_policy_t *);

int act_policy_str(const act_policy_t *, char *, const size_t);

#ifdef CONFIG_ACT_TEST

int policy_check_single_int(const act_single_cond_t *, const act_attr_t *);

int policy_check_single_str(const act_single_cond_t *, const act_attr_t *);

int policy_check_single(const act_single_cond_t *, const struct list_head *);

int policy_check(const act_cond_t *,
	const struct list_head *, const struct list_head *);

#endif

act_sign_t act_policy_check(const act_policy_t *,
	const act_cert_t *, const act_cert_t *);

void act_policy_list_init(void);

int act_policy_list_add(act_policy_t *);

struct list_head *act_policy_list(const act_action_t);

#endif /* end of include guard: __LINUX_ACT_POLICY_H */
