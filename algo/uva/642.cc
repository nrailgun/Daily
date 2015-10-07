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
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef set<string, less<string> > dv_t;
typedef map<string, dv_t> dict_t;

dict_t dict;

int main(int argc, char *argv[])
{
	string word;
	while (cin >> word) {
		if (word == "XXXXXX")
			break;
		string sorted = word;
		sort(sorted.begin(), sorted.end());
		dict[sorted].insert(word);
	}

	while (cin >> word) {
		if (word == "XXXXXX")
			break;

		string sorted = word;
		sort(sorted.begin(), sorted.end());
		dict_t::const_iterator it = dict.find(sorted);
		if (it == dict.end()) {
			cout << "NOT A VALID WORD" << endl;
		}
		else {
			for (dv_t::const_iterator it2 = it->second.begin();
				it2 != it->second.end(); it2++) {
				cout << *it2 << endl;
			}
		}
		cout << "******" << endl;
	}

	return EXIT_SUCCESS;
}
