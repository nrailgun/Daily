/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <climits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int D, I;
bool tree[1 << 21];

int main(int argc, char *argv[])
{
	int n;
	cin >> n;
	while (n--) {
		cin >> D >> I;
		memset(tree, 0, sizeof(tree));
		int nball = (1 << D) - 1;
		int leave = nball / 2; // idx >= leave, is leaf

		int idx;
		for (int i = 0; i < I; i++) {
			idx = 0;
			while (idx < leave) {
				tree[idx] = !tree[idx];
				if (!tree[idx])
					idx = 2 * idx + 2;
				else
					idx = 2 * idx + 1;
			}
		}
		printf("%d\n", 1 + idx);
	}
	return EXIT_SUCCESS;
}
