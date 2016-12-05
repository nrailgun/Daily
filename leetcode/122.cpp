// 简单求导数极大值极小值。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
         vector<int> gradients;
         int bidx = -1, sidx = -1;
         int earn = 0;
         for (int i = 0; i < prices.size(); i++) {
             if (bidx == -1) { // didn't buy
                 bool lg = prices[i-1] >= prices[i] || i == 0;
                 bool rg = prices[i+1] >  prices[i] || i == prices.size() - 1;
                 if (lg && rg) {
                     bidx = i;
                 }
             } else { // bought
                 bool ll = prices[i-1] <  prices[i] || i == 0;
                 bool rl = prices[i+1] <= prices[i] || i == prices.size() - 1;
                 if (ll && rl) {
                     sidx = i;
                     earn += prices[sidx] - prices[bidx];
                     bidx = -1;
                 }
             }
         }
         return earn;
    }
};
