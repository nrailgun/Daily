/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

static const int MAXN = 30;

int N, k, m;

typedef struct list_node {
	int v;
	struct list_node *prev, *nxt;
} list_node_t;

list_node_t nodes[MAXN];

void init_list(list_node_t *n)
{
	n->prev = n;
	n->nxt = n;
}

void list_add(list_node_t *l, list_node_t *n)
{
	list_node_t *tail = l->prev;

	tail->nxt = n;
	l->prev = n;
	n->prev = tail;
	n->nxt = l;
}

list_node_t *list_remove(const list_node_t *n)
{
	list_node_t *prev = n->prev;
	list_node_t *nxt = n->nxt;

	if (prev == n) {
		assert(nxt == n);
		return NULL;
	}

	prev->nxt = nxt;
	nxt->prev = prev;

	return nxt;
}

list_node_t *kit, *mit;

bool count(int &i1, int &i2)
{
	for (int i = 1; i < k; ++i) {
		kit = kit->nxt;
	}
	i1 = kit->v;

	for (int i = 1; i < m; ++i) {
		mit = mit->prev;
	}
	i2 = mit->v;
	
	if (kit == mit) {
		mit = mit->prev;
		kit = list_remove(kit);
		if (kit == NULL)
			return false;
	}
	else if (kit->nxt == mit) {
		assert(mit->prev = kit);

		if (kit->prev == mit)
			return false;
		mit = kit->prev;
		kit = list_remove(kit);
		kit = list_remove(kit);
	}
	else {
		list_remove(mit);
		mit = mit->prev;
		kit = list_remove(kit);
	}

	return true;
}

int main(int argc, char *argv[])
{
	while (EOF != scanf("%d %d %d", &N, &k, &m)) {
		if (N == 0)
			break;
		memset(&nodes, 0, sizeof(nodes));

		list_node_t *ls = &nodes[0];
		ls->v = 1;
		init_list(ls);
		for (int i = 1; i < N; i++) {
			nodes[i].v = i + 1;
			list_add(ls, &nodes[i]);
		}
		kit = ls;
		mit = ls->prev;

		int i1, i2;
		while (count(i1, i2)) {
			if (i1 != i2)
				printf("%3d%3d,", i1, i2);
			else
				printf("%3d,", i1);
		}
		if (i1 != i2)
			printf("%3d%3d\n", i1, i2);
		else
			printf("%3d\n", i1);
	}

	return EXIT_SUCCESS;
}
