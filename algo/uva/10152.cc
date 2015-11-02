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

int n;
vector<string> origin, target;

int main(int argc, char *argv[])
{
	int ncase;
	cin >> ncase;
	
	while (ncase--)
	{
		origin.clear(); target.clear();
		cin >> n;

		int i;
		string name;
		getline(cin, name);
		for (i = 0; i < n; ++i) {
			getline(cin, name);
			origin.push_back(name);
		}
		reverse(origin.begin(), origin.end());
		for (i = 0; i < n; ++i) {
			getline(cin, name);
			target.push_back(name);
		}
		reverse(target.begin(), target.end());

		vector<string>::const_iterator oit, tit;
		oit = origin.begin();
		for (tit = target.begin(); tit != target.end(); tit++) {
			while (oit != origin.end() && *oit != *tit)
				oit++;

			if (oit == origin.end())
				break;
			oit++;
		}

		for (; tit != target.end(); tit++) {
			cout << *tit << endl;
		}
		cout << endl;
	}
	return EXIT_SUCCESS;
}
