#include "pch.h"
#include "LeetCode.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
	int longestValidParentheses(const string &s) {
		const int n = s.size();
		int maxL = 0;

		stack<int> st;
		stack<tuple<int, int>> oks;
		for (int i = 0; i < n; i++) {
			char c = s[i];
			if (c == '(') {
				st.push(i);
			}
			else {
				if (!st.empty()) {
					int j = st.top();
					st.pop();

					while (!oks.empty()) {
						tuple<int, int> lastOk = oks.top();
						int okBeg = get<0>(lastOk);
						int okEnd = get<1>(lastOk);
						assert(okBeg < okEnd);

						if (okEnd + 1 == j) {
							oks.pop();
							j = okBeg;
						}
						else if (okBeg > j) {
							oks.pop();
						}
						else {
							break;
						}
					}
					oks.push(make_tuple(j, i));

					int l = i - j + 1;
					if (l > maxL) {
						maxL = l;
					}
				}
			}
		}
		return maxL;
	}
};

int main()
{
	Solution sol;
	assert( 2 == sol.longestValidParentheses("(()"));
	assert( 4 == sol.longestValidParentheses(")()())"));
	assert( 6 == sol.longestValidParentheses(")()())()(())"));
	assert( 2 == sol.longestValidParentheses("()(()"));
	assert( 4 == sol.longestValidParentheses("()()(()"));
	assert( 4 == sol.longestValidParentheses("()(()()"));
}
