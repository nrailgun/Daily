// Straight forward DP.
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		if (!n)
			return 0;
		vector<int> profits(n, 0);

		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				profits[i] = max(profits[i], prices[i] - prices[j] + (j >= 2 ? profits[j - 2] : 0));
			}
			profits[i] = max(profits[i], profits[i - 1]);
		}
		return profits.back();
	}
};

// 这个题目不难，但是思路很经典。
// dp[action][i] 表示以 action 为最后动作的 i-th day 的 profit，解决了 sell 只能接 cooldown，buy 只能接
// cooldown 的约束问题。

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		if (!n)
			return 0;

		vector<int> buy(n, 0), sell(n, 0), cooldown(n, 0);
		buy[0] = -prices[0];
		sell[0] = INT_MIN;
		cooldown[0] = 0;
		for (int i = 1; i < n; i++) {
			buy[i] = max(buy[i - 1], cooldown[i - 1] - prices[i]);
			sell[i] = max(sell[i - 1], buy[i - 1] + prices[i]);
			cooldown[i] = max(cooldown[i - 1], sell[i - 1]);
		}
		return max(cooldown[n - 1], max(buy[n - 1], sell[n - 1]));
	}
};
