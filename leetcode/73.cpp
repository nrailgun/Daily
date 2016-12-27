// 机智地使用了第一行和第一列用来存储信息，然后 hard coding 手动处理第一行第一列。
class Solution {
public:
    void setZeroes(vector<vector<int>>& v) {
        int m = v.size();
        int n = v[0].size();
        
        bool colzero = false;
        for (int i = 0; i < m; i++) {
            if (v[i][0] == 0)
                colzero = true;
        }
        bool rowzero = false;
        for (int i = 0; i < n; i++) {
            if (v[0][i] == 0)
                rowzero = true;
        }
        
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (v[i][j] == 0) {
                    v[i][0] = 0;
                    v[0][j] = 0;
                }
            }
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (v[i][0] == 0 || v[0][j] == 0) {
                    v[i][j] = 0;
                }
            }
        }
        
        if (rowzero) {
            for (int i = 0; i < n; i++) {
                v[0][i] = 0;
            }
        }
        if (colzero) {
            for (int i = 0; i < m; i++) {
                v[i][0] = 0;
            }
        }
    }
};
