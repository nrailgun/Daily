class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0)
            return 0;
        
        int minp = prices[0];
        int maxprof = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            int p = prices[i];
            minp = min(minp, p);
            maxprof = max(maxprof, p - minp);
        }
        return maxprof;
    }
};
