// DP。O(n^2)，别想太多没用的。

class Solution {
public:
    int solve(const string &s, int lb, int ub, vector<vector<int>> &dp) {
        if (dp[lb][ub] != -1)
            return dp[lb][ub];

        // 状态转移方程
        if (s[lb] == s[ub]) {
            dp[lb][ub] = 2 + solve(s, lb+1, ub-1, dp);
        } else {
            dp[lb][ub] = max( solve(s, lb+1, ub, dp), solve(s, lb, ub-1, dp) );
        }
        return dp[lb][ub];
    }

    int longestPalindromeSubseq(string s) {
        int n = s.size();
        if (!n)
            return 0;

        vector<vector<int>> dp(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) { // 减少 dp solve 中 if
            for (int j = 0; j < i; j++)
                dp[i][j] = 0;
            dp[i][i] = 1;
        }
        return solve(s, 0, n-1, dp);
    }
};
