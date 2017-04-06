class Solution {
public:
	bool PredictTheWinner(vector<int> &nums) {
		int n = nums.size();
		vector<vector<int>> dp(n, vector<int>(n, 0));

		for (int i = 0; i < n; i++) {
			dp[i][i] = nums[i];
		}
		for (int i = 1; i < n; i++) {
			for (int j = 0; i + j < n; j++) {
				int sc1 = nums[j] - dp[j + 1][i + j];
				int sc2 = nums[i + j] - dp[j][i + j - 1];
				dp[j][i + j] = max(sc1, sc2);
			}
		}
		return dp[0][n - 1] >= 0;
	}
};
