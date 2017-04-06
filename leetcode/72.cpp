// DP.

class Solution {
public:
    int minDistance(const string &_w1, const string &_w2) {
        int l1 = _w1.size(), l2 = _w2.size();
        string w1 = ' ' + _w1;
        string w2 = ' ' + _w2;
        
        vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1));
        
        for (int j = 0; j <= l2; j++) {
            dp[0][j] = j;
        }
        
        for (int i = 1; i <= l1; i++) {
            dp[i][0] = i;
            
            for (int j = 1; j <= l2; j++) {
                if (w1[i] == w2[j])
                    dp[i][j] = dp[i-1][j-1]; // 注意：Else 会出现 dp[i][j] 未被初始化的情况。
                else
                    dp[i][j] = dp[i-1][j-1] + 1;
                dp[i][j] = min(dp[i][j], dp[i][j-1] + 1); // Insert
                dp[i][j] = min(dp[i][j], dp[i-1][j] + 1); // Delete
            }
        }
        
        return dp[l1][l2];
    }
};
