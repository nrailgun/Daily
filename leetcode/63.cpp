// 思想很普通，但是用了多余数组 size 来处理越界的情况。
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obs) {
        int m = obs.size();
        int n = obs[0].size();
        
        vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));
        c[m][n-1] = 1;
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (obs[i][j] == 1)
                    continue;
                c[i][j] = c[i+1][j] + c[i][j+1];
            }
        }
        return c[0][0];
    }
};
