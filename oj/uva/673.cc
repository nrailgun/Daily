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

int main(int argc, char *argv[])
{
	int n;
	cin >> n;
	string buf;
	getline(cin, buf);
	while (n--) {
		getline(cin, buf);
		stack<char> st;
		bool fault = false;
		for (int i = 0; i < buf.size(); ++i) {
			if (st.empty()) {
				if (buf[i] == '(' || buf[i] == '[')
					st.push(buf[i]);
				else {
					fault = true;
					break;
				}
			}
			else if (buf[i] == '(' || buf[i] == '[') {
				st.push(buf[i]);
			}
			else { // ) ]
				char topc = st.top();
				if (topc == '(' && buf[i] == ')')
					st.pop();
				else if (topc == '[' && buf[i] == ']')
					st.pop();
				else {
					fault = true;
					break;
				}
			}
		}
		if (fault || !st.empty())
			cout << "No" << endl;
		else
			cout << "Yes" << endl;
	}
	return EXIT_SUCCESS;
}
