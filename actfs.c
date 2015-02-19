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

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>

#include "act.h"
#include "parse.h"
#include "parse_test.h"
#include "policy.h"
#include "policy_test.h"

static
void *act_seq_start(struct seq_file *sf, loff_t *off)
{
	return NULL;
}

static
void act_seq_stop(struct seq_file *sf, void *v)
{
}

static
void *act_seq_next(struct seq_file *sf, void *v, loff_t *off)
{
	return NULL;
}

static
int act_seq_show(struct seq_file *sf, void *v)
{
	return 0;
}

static const 
struct seq_operations act_policy_seq_ops = {
	.start = act_seq_start,
	.stop  = act_seq_stop,
	.next  = act_seq_next,
	.show  = act_seq_show,
};

static
int act_policy_open(struct inode *in, struct file *filp)
{
	return seq_open(filp, &act_policy_seq_ops);
}

static
ssize_t act_policy_write(struct file *filp, const char __user *buf,
		size_t sz, loff_t *off)
{
	act_policy_t *pl;
	int rv;

	pl = kmalloc(sizeof(*pl), GFP_KERNEL);
	if (!pl)
		return -ENOMEM;

	rv = act_parse_policy(pl, buf, sz);
	if (rv < 0)
		return rv;

	act_policy_list_add(pl);

	return (ssize_t) sz;
}

static const
struct file_operations act_policy_fops = {
	.owner   = THIS_MODULE,
	.open    = act_policy_open,
	.release = seq_release,
	.llseek  = seq_lseek,
	.read    = seq_read,
	.write   = act_policy_write,
};

#ifndef MODULE
static
int __init
#else
int
#endif

init_act_fs(void)
{
	proc_create("actpl", 0, NULL, &act_policy_fops);

	policy_test_check3();

	policy_test_check2();

	policy_test_check();

	policy_test_parse();

	parse_test_parse_conds();

	parse_test_remove_spaces();

	parse_test_parse_action_sign();

	return 0;
}

#ifndef MODULE
__initcall(init_act_fs);
#endif
