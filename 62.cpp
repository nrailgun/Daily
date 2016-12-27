// 思想和 DP 一样，但是程序写得不好。
class Solution {
public:
    int solve(int i, int j) {
        int m = c.size();
        int n = c[0].size();
        
        if (i >= m)
            return 0;
        if (j >= n)
            return 0;
        if (i == m - 1 && j == n - 1)
            return 1;
        if (c[i][j] != -1)
            return c[i][j];
        
        c[i][j] = solve(i + 1, j) + solve(i, j + 1);
        return c[i][j];
    }

    vector<vector<int>> c;
    int uniquePaths(int m, int n) {
        c.resize(m);
        for (int i = 0; i < m; i++) {
            c[i].resize(n);
            fill(c[i].begin(), c[i].end(), -1);
        }
        return solve(0, 0);
    }
};
// 更好的实现，避免了函数调用开销，更简洁的初始化。
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> c(m, vector<int>(n, 1));
        
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                c[i][j] = c[i+1][j] + c[i][j+1];
            }
        }
        return c[0][0];
    }
};
