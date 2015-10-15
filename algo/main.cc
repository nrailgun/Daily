/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

char buf[BUFSIZ];
int n;
char s[BUFSIZ];

class Tree
{
public:
	int n;
	Tree *l, *r;

	explicit Tree(int _n)
		: n(_n), l(NULL), r(NULL)
	{}

	Tree()
		: n(-1), l(NULL), r(NULL)
	{}

	~Tree()
	{
		if (l)
			delete l;
		if (r)
			delete r;
		l = r = NULL;
	}

	bool Empty() const {
		return n < 0;
	}
};

Tree *root;
int nempty = 0;

void insert(int n, const char s[])
{
	if (!root) {
		root = new Tree();
		nempty++;
	}
	Tree *node = root;

	while (*s != ')') {
		if (*s == 'L') {
			if (!node->l) {
				node->l = new Tree;
				nempty++;
			}
			node = node->l;
		}
		else { // *s == 'R'
			if (!node->r) {
				node->r = new Tree;
				nempty++;
			}
			node = node->r;
		}
		s++;
	}

	node->n = n; // TODO: Check Empty
	nempty--;
}

void display()
{
	if (nempty) {
		cout << "not complete" << endl;
		return;
	}

	queue<const Tree *> q;
	q.push(root);

	bool first = true;
	while (!q.empty()) {
		if (first)
			first = false;
		else
			cout << ' ';

		const Tree *t = q.front();
		cout << t->n;

		q.pop();
		if (t->l)
			q.push(t->l);
		if (t->r)
			q.push(t->r);
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	int rv;

	while (EOF != (rv = scanf("%s", buf))) {
		if (!strcmp("()", buf)) {
			display();
			delete root;
			root = NULL;
			nempty = 0;
			continue;
		}
		sscanf(buf, "(%d,%s", &n, s);
		insert(n, s);
	}

	return EXIT_SUCCESS;
}
