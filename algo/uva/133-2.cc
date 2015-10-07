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

bool visit[MAXN];

int main(int argc, char *argv[])
{
	int i;

	while (EOF != scanf("%d %d %d", &N, &k, &m)) {
		if (N == 0)
			break;
		memset(&visit, 0, sizeof(visit));

		int kidx = 0, midx = N - 1, cnt = 0;

		while (cnt < N) {
			for (i = 1; i < k; ++i) {
				do {
					kidx = (kidx + 1) % N;
				} while (visit[kidx]);
			}

			for (i = 1; i < m; ++i) {
				do {
					if (!midx--)
						midx = N - 1;
				} while (visit[midx]);
			}

			visit[kidx] = visit[midx] = true;

			if (kidx != midx) {
				printf("%3d%3d", kidx + 1, midx + 1);
				cnt += 2;
			}
			else {
				printf("%3d", kidx + 1);
				cnt++;
			}

			if(cnt == N) {
				putchar('\n');
				break;
			}
			else {
				putchar(',');
			}

			do {
				kidx = (kidx + 1) % N;
			} while (visit[kidx]);

			do {
				if (!midx--)
					midx = N - 1;
			} while (visit[midx]);
		}
	}

	return EXIT_SUCCESS;
}
