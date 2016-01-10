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
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int T, M;

int t[110], p[110];

int best[110][1010]; // grass x time

int main(int argc, char *argv[])
{
	cin >> T >> M;
	for (int i = 1; i <= M; i++) {
		cin >> t[i] >> p[i];
	}

	memset(best, 0, sizeof(best));
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= T; j++) {
			if (j < t[i]) {
				best[i][j] = best[i - 1][j];
				continue;
			}
			int psb = p[i] + best[i - 1][j - t[i]];
			if (psb <= best[i - 1][j]) {
				best[i][j] = best[i - 1][j];
			}
			else {
				best[i][j] = psb;
			}
		}
	}

	cout << best[M][T] << endl;

	return EXIT_SUCCESS;
}
