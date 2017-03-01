// 简单的 DP，根据 (i-1,j) (i,j-1) (i-1,j-1) 算 (i,j)。

class Solution {
public:
    int dp(const vector<vector<char>> &M, vector<vector<int>> &N, int i, int j) {
        int m = M.size();
        int n = M[0].size();
        
        if (i < 0 || i >= m || j < 0 || j >= n)
            return 0;
        
        if (N[i][j] != -1)
            return N[i][j];
        
        if ('0' == M[i][j])
            return (N[i][j] = 0);

        N[i][j] = 1 + min(
            dp(M, N, i-1, j-1),
            min( dp(M, N, i-1, j), dp(M, N, i, j-1) ) );
        return N[i][j];
    }

    int maximalSquare(vector<vector<char>> &M) {
        int m = M.size();
        if (!m)
            return 0;
        int n = M[0].size();
        vector<vector<int>> N(m, vector<int>(n, -1));
        
        int maxsq = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxsq = max(maxsq, dp(M, N, i, j));
            }
        }
        return maxsq * maxsq;
    }
};
