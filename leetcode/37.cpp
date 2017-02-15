// Naive DFS.
class Solution {
public:
    bool rval[9][10], cval[9][10], sval[9][10];
    
    Solution() {
    }
    
    inline int rc2k(int i, int j) {
        return i / 3 * 3 + j / 3;
    }
    
    bool dfs(vector<vector<char>> &b, int idx) {
        if (idx == 81)
            return true;
            
        int r = idx / 9, c = idx % 9;
        int k = rc2k(r, c);

        if (b[r][c] != '.') {
            return dfs(b, idx + 1);
        }
        
        for (int i = 1; i <= 9; i++) {
            if (rval[r][i] || cval[c][i] || sval[k][i])
                continue;
            b[r][c] = i + '0';
            rval[r][i] = cval[c][i] = sval[k][i] = true;
            bool rv = dfs(b, idx + 1);
            if (rv)
                return true;
            rval[r][i] = cval[c][i] = sval[k][i] = false;
        }
        
        b[r][c] = '.';
        return false;
    }

    void solveSudoku(vector<vector<char>>& b) {
        memset(rval, false, sizeof(rval));
        memset(cval, false, sizeof(cval));
        memset(sval, false, sizeof(sval));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (b[i][j] == '.')
                    continue;
                int k = rc2k(i, j);
                rval[i][b[i][j]-'0'] = cval[j][b[i][j]-'0'] = sval[k][b[i][j]-'0'] = true;
            }
        }
    
        dfs(b, 0);
    }
};
