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
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __LINUX_POLICY_TEST_H
#define __LINUX_POLICY_TEST_H

#include <linux/slab.h>

#include "Asserts.h"
#include "act.h"
#include "attr_repo.h"
#include "attr_repo_help.h"
#include "parse.h"
#include "policy.h"

static const
char *pl_rules[] = {
	"ALLOW FILE_OPEN IF { SUBJECT.security > 3; OBJECT.name = 'John'; };",
	"DENY SB_COPY_DATA IF { SUBJECT.security = 0;"
		"[ OBJECT.security = 0; OBJECT.role = 'student'; ]; };",
};

static inline
void policy_test_parse(void)
{
	const char *exp_r = "ALLOW FILE_OPEN IF "
		"{ SUBJECT . security > 3 ; OBJECT . name = 'John' ; } ; ";
	int rv;
	char *r;
	act_policy_t pl;
	size_t sz;
	act_cond_t *cond;
	act_single_cond_t *sg;

	rv = tokenize(pl_rules[0], strlen(pl_rules[0]), &r);
	ACT_Test(rv > 0);
	ACT_Test(!strcmp(r, exp_r));

	sz = rv;
	rv = act_parse_policy(&pl, r, sz);
	ACT_Test(rv == strlen(exp_r));

	cond = &pl.cond;
	ACT_Test(cond->cond_type == ACT_COND_TYPE_AND);
	ACT_Test(cond->nconds == 2);

	cond = pl.cond.conds[0];
	ACT_Test(cond->cond_type == ACT_COND_TYPE_SINGLE);

	sg = &cond->single_cond;
	ACT_Test(sg->owner == ACT_OWNER_SUBJ);
	ACT_Test(sg->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(sg->key, "security"));
	ACT_Test(sg->cmp == ACT_CMP_GREATER);
	ACT_Test(sg->intval == 3);

	cond = pl.cond.conds[1];
	ACT_Test(cond->cond_type == ACT_COND_TYPE_SINGLE);

	sg = &cond->single_cond;
	ACT_Test(cond->cond_type == ACT_COND_TYPE_SINGLE);
	ACT_Test(sg->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(sg->key, "name"));
	ACT_Test(sg->cmp == ACT_CMP_EQUAL);
	ACT_Test(!strcmp(sg->strval, "John"));
}

static inline
void policy_test_check(void)
{
	int rv;
	char *r;
	act_policy_t pl;
	size_t sz;
	act_cert_t *subj, *obj;
	act_attr_t *at;

	/*
	 * ALLOW FILE_OPEN IF {
	 * 	SUBJECT.security > 3;
	 * 	OBJECT.name = 'John';
	 * };"
	 */
	rv = tokenize(pl_rules[0], strlen(pl_rules[0]), &r);

	sz = rv;
	act_parse_policy(&pl, r, sz);

	subj = act_cert_alloc(ACT_OWNER_SUBJ);
	act_cert_add_attr(subj, ACT_ATTR_TYPE_INT, "security", (void *) 4);

	at = list_entry(subj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(at->key, "security"));
	ACT_Test(at->intval == 4);

	act_cert_add_attr(subj, ACT_ATTR_TYPE_STR, "role", "teacher");

	at = list_entry(subj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "role"));
	ACT_Test(!strcmp(at->strval, "teacher"));

	obj = act_cert_alloc(ACT_OWNER_OBJ);
	act_cert_add_attr(obj, ACT_ATTR_TYPE_STR, "role", "object_ta");

	at = list_entry(obj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "role"));
	ACT_Test(!strcmp(at->strval, "object_ta"));

	act_cert_add_attr(obj, ACT_ATTR_TYPE_STR, "name", "John");

	at = list_entry(obj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "name"));
	ACT_Test(!strcmp(at->strval, "John"));

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 1);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_ALLOW);
}

static inline
void policy_test_check2(void)
{
	int rv;
	char *r;
	act_policy_t pl;
	size_t sz;
	act_cert_t *subj, *obj;
	act_attr_t *at;

	/*
	 * ALLOW FILE_OPEN IF {
	 * 	SUBJECT.security > 3;
	 * 	OBJECT.name = 'John';
	 * };"
	 */
	rv = tokenize(pl_rules[0], strlen(pl_rules[0]), &r);

	sz = rv;
	act_parse_policy(&pl, r, sz);

	subj = act_cert_alloc(ACT_OWNER_SUBJ);
	obj = act_cert_alloc(ACT_OWNER_OBJ);

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);

	/* add attr role */
	act_cert_add_attr(subj, ACT_ATTR_TYPE_STR, "role", "teacher");

	at = list_entry(subj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "role"));
	ACT_Test(!strcmp(at->strval, "teacher"));

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);

	/* obj attr role */
	act_cert_add_attr(obj, ACT_ATTR_TYPE_STR, "role", "object_ta");

	at = list_entry(obj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "role"));
	ACT_Test(!strcmp(at->strval, "object_ta"));

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);

	/* add attr security */
	act_cert_add_attr(subj, ACT_ATTR_TYPE_INT, "security", (void *) 4);

	at = list_entry(subj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(at->key, "security"));
	ACT_Test(at->intval == 4);

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);

	/* obj attr name */
	act_cert_add_attr(obj, ACT_ATTR_TYPE_STR, "name", "Jerk");

	at = list_entry(obj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "name"));
	ACT_Test(!strcmp(at->strval, "Jerk"));

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);
}

static inline
void policy_test_check3(void)
{
	int rv;
	char *r;
	act_policy_t pl;
	size_t sz;
	act_cert_t *subj, *obj;
	act_attr_t *at;

	/*
	 * DENY SB_COPY_DATA IF {
	 * 	SUBJECT.security = 0;
	 * 	[ OBJECT.security = 0; OBJECT.role = 'student'; ];
	 * };
	 */
	rv = tokenize(pl_rules[1], strlen(pl_rules[1]), &r);

	sz = rv;
	act_parse_policy(&pl, r, sz);

	subj = act_cert_alloc(ACT_OWNER_SUBJ);
	obj = act_cert_alloc(ACT_OWNER_OBJ);

#if 1
	/* Check empty */
	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);
#endif

	/* Check subj role */
	act_cert_add_attr(subj, ACT_ATTR_TYPE_STR, "role", "teacher");

#if 1
	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);
#endif

	/* Check subj security */
	act_cert_add_attr(subj, ACT_ATTR_TYPE_INT, "security", (void *) 0);
	at = list_entry(subj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(at->key, "security"));
	ACT_Test(at->intval == 0);

#if 1
	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);
#endif

	/* Check obj security */
	act_cert_add_attr(obj, ACT_ATTR_TYPE_INT, "security", (void *) 1);

	at = list_entry(subj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(at->key, "security"));
	ACT_Test(at->intval == 0);
	
	at = list_entry(obj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(at->key, "security"));
	ACT_Test(at->intval == 1);
#if 1
	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 0);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_NOT_APPLICABLE);
#endif

	/* Check obj role */
	act_cert_add_attr(obj, ACT_ATTR_TYPE_STR, "role", "student");

	at = list_entry(obj->attrs.prev, act_attr_t, list);
	ACT_Test(at->type == ACT_ATTR_TYPE_STR);
	ACT_Test(!strcmp(at->key, "role"));
	ACT_Test(!strcmp(at->strval, "student"));

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 1);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_DENY);
}

static inline
void policy_test_check4(void)
{
	const char *rs[] = {
		"DENY FILE_PERMISSION IF { SUBJECT.security < 2; "
			"OBJECT.name = 'Admin'; };",
		"DENY FILE_PERMISSION IF { SUBJECT.security = 0;"
			"[ OBJECT.security > 0; OBJECT.role = 'Teacher'; ]; };",
	};

	int rv;
	act_policy_t pl;
	act_cert_t *subj, *obj;
	char buf[500];

	rv = act_parse_policy(&pl, rs[0], strlen(rs[0]));
	ACT_Assert(rv > 0);

	act_policy_str(&pl, buf, 500);

	subj = act_cert_alloc(ACT_OWNER_SUBJ);
	act_cert_add_attr(subj, ACT_ATTR_TYPE_STR, "name", "John");
	act_cert_add_attr(subj, ACT_ATTR_TYPE_STR, "role", "Student");
	act_cert_add_attr(subj, ACT_ATTR_TYPE_INT, "security", 0);
	act_cert_str(subj, buf, 500);

	obj = act_cert_alloc(ACT_OWNER_OBJ);
	act_cert_add_attr(obj, ACT_ATTR_TYPE_STR, "name", "Admin");
	act_cert_add_attr(obj, ACT_ATTR_TYPE_INT, "security", 0);
	act_cert_str(obj, buf, 500);

	rv = policy_check(&pl.cond, &subj->attrs, &obj->attrs);
	ACT_Test(rv == 1);

	rv = act_policy_check(&pl, subj, obj);
	ACT_Test(rv == ACT_SIGN_DENY);
}

#endif /* end of include guard: __LINUX_POLICY_TEST_H */
