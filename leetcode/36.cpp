class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& b) {
        bool rval[9][10], cval[9][10], sval[9][10];
        memset(rval, false, sizeof(rval));
        memset(cval, false, sizeof(cval));
        memset(sval, false, sizeof(sval));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (b[i][j] == '.')
                    continue;
                int k = i / 3 * 3 + j / 3;
                int v = b[i][j] - '0';
                if (rval[i][v] || cval[j][v] || sval[k][v]) {
                    return false;
                }
                rval[i][v] = cval[j][v] = sval[k][v] = true;
            }
        }
        return true;
    }
};
