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

#ifndef __LINUX_SECURITY_ACT_H
#define __LINUX_SECURITY_ACT_H

#include <linux/printk.h>

#define CONFIG_ACT_TEST

#define CONFIG_ACT_TEST_LSM

// #define CONFIG_ACT_DEBUG_INFO
 
// #define CONFIG_ACT_VERB_INFO

#define ACT_Info(fmt, args...)						\
	do {								\
		printk(KERN_INFO "Act: " fmt "\n", ##args);		\
	} while (0)

#define ACT_Warn(fmt, args...)						\
	do {								\
		if (printk_ratelimit())					\
			printk(KERN_WARNING "Act: " fmt "\n", ##args);	\
	} while (0)

#define ACT_Error(fmt, args...)						\
	do {								\
		if (printk_ratelimit())					\
			printk(KERN_ERR "Act: " fmt "\n", ##args);	\
	} while (0)

int act_debug_flag(void);

void act_set_debug_flag(void);

void act_reset_debug_flag(void);

#endif /* end of include guard: __LINUX_SECURITY_ACT_H */
