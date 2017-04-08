// 水题，通过递归实现 DP 就可以了。

class Solution {
public:
	map<pair<int, int>, bool> dp;

	bool isInterleave(const string &s1, int i1, const string &s2, int i2, const string &s3) {
		int n1 = s1.size(), n2 = s2.size();
		int n3 = s3.size();
		int i3 = i1 + i2;

		if (i3 == n3)
			return true;
		
		auto p = make_pair(i1, i2);
		auto it = dp.find(p);
		if (it != dp.end())
			return it->second;

		bool dpp = false;
		if (i1 < n1 && s1[i1] == s3[i3]) {
			dpp = dpp || isInterleave(s1, i1 + 1, s2, i2, s3);
		}
		if (i2 < n2 && s2[i2] == s3[i3]) {
			dpp = dpp || isInterleave(s1, i1, s2, i2 + 1, s3);
		}
		return dp[p] = dpp;
	}

	bool isInterleave(const string &s1, const string &s2, const string &s3) {
		int n1 = s1.size(), n2 = s2.size();
		int n3 = s3.size();
		if (n3 != n1 + n2)
			return false;

		dp.clear();
		return isInterleave(s1, 0, s2, 0, s3);
	}
};
