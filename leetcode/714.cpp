class Solution {
public:
	int maxProfit(vector<int> &prices, int fee) {
		int n = prices.size();
		if (n == 0) {
			return 0;
		}
		vector<vector<int>> dp(2, vector<int>(n, 0));
		int maxbuy = INT_MIN, maxsell = 0;
		for (int i = 0; i < n; i++) {
			{
				int p = maxsell - prices[i];
				dp[0][i] = p;
				maxbuy = max(maxbuy, p);
			}
			{
				int p = maxbuy + prices[i] - fee;
				dp[1][i] = p;
				maxsell = max(maxsell, p);
			}
		}
		return max(0, *max_element(dp[1].begin(), dp[1].end()));
	}
};
