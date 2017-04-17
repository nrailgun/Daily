class Solution {
public:
	int findTargetSumWays(const vector<int>& nums, int S) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (S > sum || S < -sum)
			return 0;

		int n = nums.size();
		vector<vector<int>> dp(n, vector<int>(2 * sum + 1, 0));
		
		// dp[0][sum - nums[0]] = (dp[0][sum + nums[0]] = 1);
		// Special case nums[0] == 0
		dp[0][sum - nums[0]]++;
		dp[0][sum + nums[0]]++;

		for (int i = 1; i < n; i++) {
			for (int j = -sum; j <= sum; j++) {
				int k = j + sum;

				if (j - nums[i] >= -sum) { // +nums[i]
					dp[i][k] += dp[i - 1][k - nums[i]];
				}
				if (j + nums[i] <= sum) { // -nums[i]
					dp[i][k] += dp[i - 1][k + nums[i]];
				}
			}
		}
		return dp[n - 1][S + sum];
	}
};
