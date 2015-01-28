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
 * Copyright (C) Junyu wu, shibuyanorailgun@foxmail, 2014.
 */

#ifndef __LINUX_ACT_POLICY_H
#define __LINUX_ACT_POLICY_H

#include <linux/list.h>

/*
 * Security level. Those with security level &ACT_TRIVIAL has minimal privileges,
 * and those with security level &SECRET has maximal privileges.
 */
enum act_sec_lv
{
	ACT_TRIVIAL	= 0,
	ACT_ROUTINE	= 1,
	ACT_SYSTEMATIC	= 2,
	ACT_SECRET	= 3
};

/*
 * Security role. &GUEST for untrusted subject while &SUPERROOT for FULL access
 * to everything.
 */
enum act_role
{
	ACT_GUEST	= 0,
	ACT_USER	= 1,
	ACT_ADMIN	= 2,
	ACT_SUPERROOT	= 3
};

enum act_action
{
	ACT_ACTION_BPRM_SET_CREDS,
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
};

struct act_subj_ctx
{
	enum act_sec_lv sslv;
	enum act_role srole;
};

struct act_obj_ctx
{
	enum act_sec_lv oslv;
	enum act_role orole;
};

enum act_cmp
{
	ACT_EQUAL		= 0,
	ACT_LESS_EQUAL		= 1,
	ACT_GREATER_EQUAL	= 2
};

struct act_sec_lv_cond
{
	enum act_cmp cmp;
	enum act_sec_lv slv;
	struct list_head list;
};

struct act_role_cond
{
	enum act_cmp cmp;
	enum act_role role;
	struct list_head list;
};

enum act_sign
{ 
	ACT_NOT_APPLICABLE	= 0,
	ACT_DENY		= 1,
	ACT_ALLOW		= 2
};

struct act_policy
{
	struct list_head sslv_conds;
	struct list_head srole_conds;
	struct list_head oslv_conds;
	struct list_head orole_conds;

	enum act_action action;
	enum act_sign sign;

	struct list_head list;
};

extern struct list_head act_policies;

const char *act_sec_lv_str(enum act_sec_lv lv);

const char *act_role_str(const enum act_role role);

const char *act_cmp_str(enum act_cmp cmp);

const char *act_action_str(const enum act_action act);

const char *act_sign_str(const enum act_sign sign);

/*
 * Init &act_subj_ctx with security level &slv and role &role.
 *
 * @slv: security level.
 * @role: security role.
 */
#define ACT_SUBJ_CTX_INIT(slv, role) {		\
	.sslv = slv, .srole = role		\
}

/*
 * Init &act_subj_ctx with security level &slv and role &role.
 *
 * @slv: security level.
 * @role: security role.
 */
void act_init_subj_ctx(struct act_subj_ctx *ctx,
		const enum act_sec_lv slv, const enum act_role role);

/*
 * Init &act_obj_ctx with security level &slv and role &role.
 *
 * @slv: Security level.
 * @role: Security role.
 */
#define ACT_OBJ_CTX_INIT(slv, role) {		\
	.oslv = slv, .orole = role		\
}

/*
 * Init &act_obj_ctx with security level &slv and role &role.
 *
 * @slv: Security level.
 * @role: Security role.
 */
void act_init_obj_ctx(struct act_obj_ctx *ctx,
		const enum act_sec_lv slv, const enum act_role role);

/*
 * Init act_sec_lv_cond with @cmp and @slv.
 */
void act_init_sec_lv_cond(struct act_sec_lv_cond *cond,
		const enum act_cmp cmp, const enum act_sec_lv slv);

/*
 * Init act_role_cond with @cmp and @role.
 */
void act_init_role_cond(struct act_role_cond *cond,
		const enum act_cmp cmp, const enum act_role role);

/*
 * Init act_policy with @action and @sign, leaving all subjective / objective
 * condition lists empty.
 */
void act_init_policy(struct act_policy *pl,
		const enum act_action action, const enum act_sign sign);

/*
 * Convert act_policy into C string.
 */
const char *act_policy_str(const struct act_policy *pl);

/*
 * Add @pl to policy list for permission checking.
 *
 * @pl: Policy to add.
 *
 * Return 0 on success.
 */
void act_add_policy(struct act_policy *pl);

/*
 * Check if request &action is permitted with given &pl, &sav and &oav.
 *
 * @pl: Policy.
 * @sav: Subject attributes.
 * @oav: Object attributes.
 * @action: Request sent.
 *
 * Return !0 if permitted.
 */
int act_policy_check(struct act_policy *,
		const struct act_subj_ctx *, const struct act_obj_ctx *,
		enum act_action);

#endif /* end of include guard: __LINUX_ACT_POLICY_H */
