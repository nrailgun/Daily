class Solution {
public:
	vector<int> balls;
	vector<vector<int>> dp;

	int solve(int li, int ri) {
		if (li >= ri - 1) {
			return 0;
		}
		if (dp[li][ri] != -1) {
			return dp[li][ri];
		}

        // nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
        // 摘取的过程太难，那么反过来处理。我操这他妈的有点难想到。
		int maxcoin = 0;
		for (int i = li + 1; i < ri; i++) {
			int coin = balls[i] * balls[li] * balls[ri];
			coin += solve(li, i);
			coin += solve(i, ri);
			dp[li][ri] = max(dp[li][ri], coin);
		}
		return dp[li][ri];
	}

	int maxCoins(vector<int> &nums) {
		int n = nums.size();
		balls = vector<int>(n + 2, 1);
		for (int i = 0; i < n; i++) {
			balls[i + 1] = nums[i];
		}
		dp = vector<vector<int>>(n + 2, vector<int>(n + 2, -1));
		return solve(0, n + 1);
	}
};
