class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        if (n == 0)
            return vector<int>({});
        vector<pair<int, int>> dp(n, make_pair(1, -1));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (nums[j] % nums[i] == 0) {
                    // dp[i] = max(dp[i], 1 + dp[j]);
                    if (dp[j].first + 1 > dp[i].first) {
                        dp[i].first = dp[j].first + 1;
                        dp[i].second = j;
                    }
                }
            }
        }
        
        int maxi = max_element(dp.begin(), dp.end()) - dp.begin();
        vector<int> rv;
        while (maxi != -1) {
            rv.push_back(nums[maxi]);
            maxi = dp[maxi].second;
        }
        return rv;
    }
};
