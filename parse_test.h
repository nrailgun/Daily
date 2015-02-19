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

#ifndef __LINUX_ACT_PARSE_TEST_H
#define __LINUX_ACT_PARSE_TEST_H

#include "Asserts.h"
#include "parse.h"

static inline
int parse_test_remove_spaces(void)
{ 
	char *r, *p;
       
	r = "{Go='String'}";
	_tokenize(r, strlen(r), &p);
	ACT_Test(!strcmp(p, "{ Go = 'String' } "));

	r = "  {  Go=   123}";
	_tokenize(r, strlen(r), &p);
	ACT_Test(!strcmp(p, "{ Go = 123 } "));

	r = "DENY FILE_OPEN IF {lv>3;role~ta};";
	_tokenize(r, strlen(r), &p);
	ACT_Test(!strcmp(p, "DENY FILE_OPEN IF { lv > 3 ; role ~ ta } ; "));

	return 0;
}

static const
char *rules[] = {
	"ALLOW FILE_PERMISSION IF { } ; ",
	"{ SUBJECT . security > 3 ; [ OBJECT . role = 'student' ; ] ; } ; "
};

static inline
int parse_test_parse_action_sign(void)
{
	int i;
	size_t sz;
	act_policy_t pl;
	const char *rule = rules[0];

	sz = strlen(rules[0]);

	i = _parse_policy_sign(&pl, rule, sz);
	ACT_Test(i == 6);
	ACT_Test(pl.sign == ACT_SIGN_ALLOW);

	i += _parse_policy_action(&pl, &rule[i], sz - i);
	ACT_Test(i == 25);
	ACT_Test(pl.action == ACT_ACTION_FILE_PERMISSION);

	return 0;
}

static inline
int parse_test_parse_conds(void)
{
	const char *r;
	size_t sz;
	act_cond_t *cond, *cond1, *cond2;
	act_single_cond_t *sg;
	int i;
	char buf[100];

	r = rules[1];
	sz = strlen(r);

	cond = act_new_cond();
	i = _parse_multi_conds(cond, r, sz);
	ACT_Test(i == strlen(r));

	ACT_Test(cond->cond_type == ACT_COND_TYPE_AND);
	ACT_Test(cond->nconds == 2);

	cond1 = cond->conds[0];
	ACT_Test(cond1->cond_type == ACT_COND_TYPE_SINGLE);
	sg = &cond1->single_cond;
	ACT_Test(sg->type == ACT_ATTR_TYPE_INT);
	ACT_Test(!strcmp(sg->key, "security"));
	ACT_Test(sg->cmp == ACT_CMP_GREATER);
	ACT_Test(sg->intval == 3);

	act_single_cond_str(sg, buf, 100);

	cond2 = cond->conds[1];
	ACT_Test(cond2->cond_type == ACT_COND_TYPE_OR);
	ACT_Test(cond2->conds[0]->cond_type == ACT_COND_TYPE_SINGLE);

	sg = &cond2->conds[0]->single_cond;
	ACT_Test(!strcmp(sg->key, "role"));
	ACT_Test(!strcmp(sg->strval, "student"));

	return i;
}

#endif /* end of include guard: __LINUX_ACT_PARSE_TEST_H */
