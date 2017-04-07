// Typical Pack Problem.

class Solution {
public:
	int combinationSum4(vector<int>& nums, int target) {
		int n = nums.size();
		vector<int> dp(target + 1, 0);

		for (int j = 1; j <= target; j++) {
			for (int i = 0; i < n; i++) {
				if (nums[i] == j)
					dp[j] += 1;
				else if (nums[i] < j)
					dp[j] += dp[j - nums[i]];
			}
		}
		return dp[target];
	}
};
