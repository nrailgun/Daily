// Trivial DP.
class Solution {
public:
    bool wordBreak(string s, vector<string> &_ws) {
        int n = s.size();
        unordered_set<string> ws(_ws.begin(), _ws.end());
        
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            // dp[i] = false;
            for (int j = 0; j < i; j++) {
                if (!dp[j])
                    continue;
                if (ws.find(s.substr(j, i - j)) != ws.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
};
