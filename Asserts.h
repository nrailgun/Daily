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

#ifndef __LINUX_ACT_ASSERTS_H
#define __LINUX_ACT_ASSERTS_H

#include "act.h"

#ifdef __KERNEL__

#ifdef CONFIG_ACT_TEST

#define ACT_Assert(stat) 						\
	do {								\
		if (!(stat)) {						\
			ACT_Info("%s:%d: Assertion `" #stat		\
				"' failed.", __FILE__, __LINE__);	\
		}							\
	} while (0)

#else

#define ACT_Assert(stat)

#endif

#else /* __KERNEL__ */

#include <assert.h>

#define ACT_Assert(stat) assert(stat)

#endif /* __KERNEL__ */

#define ACT_Assert_exec(s)			\
	do {					\
		ACT_Info("%s\n", s);		\
		ACT_Assert(0);			\
	} while (0)

#define ACT_Test(stat)						\
	do {							\
		if (stat) {					\
			ACT_Info("Test success.");		\
		}						\
		else {						\
			ACT_Info("%s:%d: Test `" #stat		\
				"' failed.",			\
				__FILE__, __LINE__);		\
		}						\
	} while (0)

#endif /* end of include guard: __LINUX_ACT_ASSERTS_H */
