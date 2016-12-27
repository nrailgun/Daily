class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<int>> c(m + 1, vector<int>(n + 1, INT_MAX));
        c[m][n-1] = 0;
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                c[i][j] = min(c[i+1][j], c[i][j+1]) + grid[i][j];
            }
        }
        return c[0][0];
    }
};
