#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cstring>

#include <set>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>

using namespace std;

#define TEST

int solve1(const string &s) {
	int n = s.size();

	vector<vector<int>> dp(n, vector<int>(n, 0));
	
	int rv = 0;
	for (int diag = 0; diag < n; diag++) {
		for (int i = 0; diag + i < n; i++) {
			int j = diag + i;
			if (diag == 0) {
				dp[i][i] = 1;
			}
			else if (s[i] == s[j]) {
				dp[i][j] = dp[i + 1][j - 1] + 2;
			}
			else {
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
			}
			rv = max(rv, dp[i][j]);
		}
	}
	return rv;
}

void solve2(string &s) {
	int n = s.size();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (isupper(s[j]) && islower(s[j + 1])) {
				swap(s[j], s[j + 1]);
			}
		}
	}
}

string test_solve2(string s) {
	string o;

	for (int i = 0; i < s.size(); i++) {
		if (islower(s[i]))
			o.push_back(s[i]);
	}
	for (int i = 0; i < s.size(); i++) {
		if (isupper(s[i]))
			o.push_back(s[i]);
	}
	return o;
}

int main(int argc, char* argv[])
{
#ifdef TEST
	freopen("Text.txt", "r", stdin);
#endif

	int N;
	while (cin >> N) {
		vector<int> a(N);
		for (int i = 0; i < N; i++)
			cin >> a[i];
		sort(a.begin(), a.end());
		int minv = a.front(), maxv = a.back();

		int maxd = a[N - 1] - a[0];
		int mind = INT_MAX;
		for (int i = 1; i < N; i++) {
			mind = min(mind, a[i] - a[i - 1]);
		}

		int mincnt = 0;
		unordered_multiset<int> as(a.begin(), a.end());
		for (int i = 0; i < N; i++) {
			if (mind != 0) {
				mincnt += as.count(a[i] - mind);
			}
			else {
			}
		}

		int maxcnt = 0;
		int nminv = count(a.begin(), a.end(), minv);
		int nmaxv = count(a.begin(), a.end(), maxv);
		cout << nminv * nmaxv << endl;
	}

#ifdef TEST
	freopen("CON", "r", stdin);
	system("pause");
#endif
	return 0;
}
