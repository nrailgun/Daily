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

int n;

int bins[MAXN];

list<int> piles[MAXN];

void move_back(list<int> &pile, int block)
{
	while (pile.back() != block) {
		int b = pile.back();
		pile.pop_back();
		piles[b].push_back(b);
		bins[b] = b;
	}
	pile.pop_back();
}

void move(int a, int b, char *cmd2)
{
	list<int> &apile = piles[bins[a]];
	list<int> &bpile = piles[bins[b]];

	move_back(apile, a);

	if (!strcmp(cmd2, "onto")) {
		move_back(bpile, b);
		bpile.push_back(b);
	}

	bpile.push_back(a);
	bins[a] = bins[b];
}

void pile(int a, int b, char *cmd2)
{
	list<int> &apile = piles[bins[a]];
	list<int> &bpile = piles[bins[b]];

	if (!strcmp(cmd2, "onto")) {
		move_back(bpile, b);
		bpile.push_back(b);
	}

	for (list<int>::iterator it = apile.begin(); it != apile.end(); it++)
	{
		assert(it != apile.end());

		if (*it == a) {
			bpile.insert(bpile.end(), it, apile.end());

			for (list<int>::iterator it2 = it; it2 != apile.end();
				it2++) {
				bins[*it2] = bins[b];
			}
			apile.erase(it, apile.end());
			break;
		}
	}
}

void display()
{
	for (int i = 0; i < n; i++) {
		cout << i << ":";
		for (list<int>::const_iterator it = piles[i].begin();
			it != piles[i].end(); it++)
		{
			cout << ' ' << *it;
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	char cmd1[10], cmd2[10];
	int a, b, i;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		piles[i].push_back(i);
		bins[i] = i;
	}
	//display();

	while (EOF != scanf("%s %d %s %d", cmd1, &a, cmd2, &b)) {
		if (!strcmp("quit", cmd1))
			break;

		//printf("a: %d b: %d\n", a, b);
		if (a == b)
			continue;
		if (bins[a] == bins[b])
			continue;

		if (!strcmp("move", cmd1))
			move(a, b, cmd2);
		else
			pile(a, b, cmd2);
		//display();
	}
	display();

	return EXIT_SUCCESS;
}
