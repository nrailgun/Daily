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

char pre[32];
char in[32];
char post[32];

void solve(const char pre[], const char in[], int l)
{
	if (!l)
		return;

	char r = pre[0];
	int ridx;
	for (ridx = 0; ridx < l; ridx++) {
		if (r == in[ridx])
			break;
	}

	solve(pre + 1, in, ridx);
	solve(pre + 1 + ridx, in + 1 + ridx, l - ridx - 1);
	cout << r;
}

int main(int argc, char *argv[])
{
	while (cin >> pre >> in) {
		solve(pre, in, strlen(in));
		cout << endl;
	}

	return EXIT_SUCCESS;
}
