// 思路非常简单，就是缓存暴力搜索的结果，cpu beat 100%。

class Solution {
public:
	vector<vector<int>> dp;

	bool isMatch(const string &s, const string &p) {
		int ns = s.size(), np = p.size();
		dp = vector<vector<int>>(ns + 1, vector<int>(np + 1, -1));
		return _isMatch(s, 0, p, 0);
	}

	bool _isMatch(const string &s, int si, const string &p, int pi) {
		int ns = s.size(), np = p.size();
		if (pi >= np) {
			return si >= ns;
		}

		if (-1 != dp[si][pi]) {
			return dp[si][pi] == 1;
		}

		bool firstMatch = (si < ns) && (p[pi] == '.' || p[pi] == s[si]);
		bool a;
		if (pi + 1 < np && p[pi + 1] == '*') {
			if (_isMatch(s, si, p, pi + 2)) {
				a = true;
			}
			else {
				a = firstMatch && _isMatch(s, si + 1, p, pi);
			}
		}
		else {
			a = firstMatch && _isMatch(s, si + 1, p, pi + 1);
		}
		dp[si][pi] = a ? 1 : 0;
		return a;
	}
};
