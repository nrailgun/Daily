// 部分背包问题。贪心算法。
// 基础背包问题，或 0-1 背包问题，物体取 0 或 1 个。
// 完全背包问题，物体取任意多个。硬币找零：硬币面额固定，目标给定，数量不定，求最小总枚数，见 LeetCode 322 Coin Change。
// 多重背包问题。

// 0-1 背包问题，状态转移矩阵：(物品, 重量) 或者是 (物品, 限制目标)。
// 算法没有问题，时间复杂度应该较难优化。不过实现太过繁琐，速度缓慢，另外，状态转移矩阵只需要 2 层，可以优化空间使用效率。
class Solution {
public:
    int dp(vector<vector<int>> &M, int i, int j, const vector<int> &nums) {
        int n = M.size(), m = M[0].size();
        if (j == 0) {
            return 0;
        }
        if (i >= n || j < 0) {
            return INT_MAX;
        }
        if (M[i][j] != -1) {
            return M[i][j];
        }

        M[i][j] = min( dp(M, i+1, j, nums), dp(M, i+1, j-nums[i], nums) );
        if (M[i][j] != INT_MAX)
            ++M[i][j];
        return M[i][j];
    }

    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (!n)
            return false;
        int m = accumulate(nums.begin(), nums.end(), 0);
        if (m % 2)
            return false;
        m /= 2;
        
        vector<vector<int>> M(n, vector<int>(m+1, -1));
        return INT_MAX != dp(M, 0, m, nums);
    }
};

// 避免函数开销。实际上步长也不需要计算。
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (!n)
            return false;
        int m = accumulate(nums.begin(), nums.end(), 0);
        if (m % 2)
            return false;
        m /= 2;
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= m; i++)
            dp[0][i] = INT_MAX;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int s1 = dp[i-1][j], s2 = INT_MAX;
                if (j >= nums[i-1])
                    s2 = dp[i-1][j-nums[i-1]];
                dp[i][j] = min(s1, s2);
                if (dp[i][j] != INT_MAX)
                    dp[i][j]++;
            }
        }
        return dp[n][m] != INT_MAX;
    }
};

// 直接只算 bool。
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (!n)
            return false;
        int m = accumulate(nums.begin(), nums.end(), 0);
        if (m % 2)
            return false;
        m /= 2;
        
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, true));
        for (int i = 1; i <= m; i++)
            dp[0][i] = false;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int s1 = dp[i-1][j], s2 = false;
                if (j >= nums[i-1])
                    s2 = dp[i-1][j-nums[i-1]];
                dp[i][j] = s1 || s2;
            }
        }
        return dp[n][m];
    }
};
