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

int D, I;

int main(int argc, char *argv[])
{
	int n;
	cin >> n;
	while (n--) {
		cin >> D >> I;
		int nball = (1 << D) - 1;
		int leave = nball / 2; // idx >= leave, is leaf

		int idx = 0;
		while (idx < nball) {
			if (I % 2) {
				idx = 2 * idx + 1;
				I = I / 2 + 1;
			}
			else {
				idx = 2 * idx + 2;
				I /= 2;
			}

			if (idx >= leave) {
				cout << idx + 1 << endl;
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}
