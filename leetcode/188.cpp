class Solution {
public:
	int maxProfit(int k, vector<int> &prices) {
		int n = prices.size();
		if (n == 0) {
			return 0;
		}

		// 剪枝，退化成贪心。
		if (k >= n) {
			int maxprofit = 0;
			for (int i = 1; i < n; i++) {
				int p = prices[i] - prices[i - 1];
				if (p > 0) {
					maxprofit += p;
				}
			}
			return maxprofit;
		}

		vector<vector<int>> dp(2, vector<int>(n, 0));
		for (int i = 0; i < 2 * k; i++) {
			int currow = i % 2;
			int prevrow = (i + 1) % 2;
			int curmaxprofit = dp[prevrow][0];
			for (int j = 0; j < n; j++) {
				curmaxprofit = max(curmaxprofit, dp[prevrow][j]);
				if (i % 2 == 0) {
					dp[currow][j] = curmaxprofit - prices[j];
				}
				else {
					dp[currow][j] = curmaxprofit + prices[j];
				}
			}
		}
		return *max_element(dp[1].begin(), dp[1].end());
	}
};
