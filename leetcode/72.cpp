// DP.

class Solution {
public:
    int minDistance(const string &w1, const string &w2) {
        int l1 = w1.size(), l2 = w2.size();
        vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1));

        for (int j = 0; j <= l2; j++) {
            dp[0][j] = j;
        }
        for (int i = 1; i <= l1; i++) {
            dp[i][0] = i;
            
            for (int j = 1; j <= l2; j++) {
                if (w1[i-1] == w2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
                    dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
                }
            }
        }
        return dp[l1][l2];
    }
};

// 滚动数组。不过不太好滚动，需要一些辅助变量。
class Solution {
public:
    int minDistance(const string &w1, const string &w2) {
        int l1 = w1.size(), l2 = w2.size();
        vector<int> dp(l2 + 1);

        for (int j = 0; j <= l2; j++) {
            dp[j] = j;
        }
        for (int i = 1; i <= l1; i++) {
            dp[0] = i;
            
            int v1 = i - 1; // 辅助变量1
            for (int j = 1; j <= l2; j++) {
                int v2 = dp[j]; // 辅助变量2
                if (w1[i-1] == w2[j-1])
                    dp[j] = v1;
                else {
                    dp[j] = min(v1 + 1, min(dp[j-1] + 1, dp[j] + 1));
                }
                v1 = v2;
            }
        }
        return dp[l2];
    }
};
