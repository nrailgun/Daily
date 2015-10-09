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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int N;
vector<int> seq;
stack<int> trains;

int main(int argc, char *argv[])
{
	bool first = true;
	while (cin >> N) {
		if (!N)
			break;
#if 0
		if (first)
			first = false;
		else
			cout << endl;
#endif

		int t;
		while (cin >> t) {
			if (!t)
				break;
			seq.clear();
			seq.push_back(t);
			for (int i = 1; i < N; ++i) {
				cin >> t;
				seq.push_back(t);
			}
#if 0
			for (int i = 0; i < seq.size(); ++i) {
				cout << seq[i] << ' ';
			}
			cout << endl;
#endif

			for (int i = 0, j = 1; i < N; i++) {
				int t = seq[i];
				if (trains.empty())
					trains.push(j++);
				while (j <= N && trains.top() != t)
					trains.push(j++);
				if (trains.top() != t)
					goto for_out;
				else
					trains.pop();
			}
for_out:
			if (!trains.empty()) {
				while (!trains.empty())
					trains.pop();
				cout << "No" << endl;
			}
			else
				cout << "Yes" << endl;
		}
		cout << endl;
	}
	return EXIT_SUCCESS;
}
