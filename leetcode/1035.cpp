class Solution {
public:
	vector<vector<int>> dp;

	int solve(const vector<int> &a, int ai, const vector<int> &b, int bi) {
		if (ai == -1 || bi == -1) {
			return 0;
		}
		if (dp[ai][bi] != -1) {
			return dp[ai][bi];
		}

		if (a[ai] == b[bi]) {
			dp[ai][bi] = solve(a, ai - 1, b, bi - 1) + 1;
		}
		else {
			dp[ai][bi] = max(solve(a, ai - 1, b, bi), solve(a, ai, b, bi - 1));
		}
		return dp[ai][bi];
	}

	int maxUncrossedLines(vector<int> &a, vector<int> &b) {
		int na = a.size();
		int nb = b.size();
		dp = vector<vector<int>>(na, vector<int>(nb, -1));
		return solve(a, na - 1, b, nb - 1);
	}
};
