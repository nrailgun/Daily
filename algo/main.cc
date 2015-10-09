/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <algorithm>
#include <cassert>
#include <cmath>
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

int n;
vector<string> files;

bool strlen_cmp(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

int main(int argc, char *argv[])
{
	while (cin >> n) {
		files.clear();
		for (int i = 0; i < n; ++i) {
			string fname;
			cin >> fname;
			files.push_back(fname);
		}

		sort(files.begin(), files.end());
		vector<string>::const_iterator it;
		it = max_element(files.begin(), files.end(), strlen_cmp);

		int L = min(it->size() + 2, string::size_type(60));
		int C = 60 / L;
		int R = (files.size() + C - 1) / C;

		for (int i = 0; i < 60; ++i)
			putchar('-');
		putchar('\n');

		char fmt[29];
		snprintf(fmt, 29, "%%-%ds", L);

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; ++j) {
				int idx = j * R + i;
				if (idx >= files.size())
					break;
				const string fname = files[idx];
				printf(fmt, fname.c_str());
			}
			printf("\n");
		}
	}
	return EXIT_SUCCESS;
}
