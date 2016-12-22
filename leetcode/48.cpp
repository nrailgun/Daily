// rotate 再 reverse。
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        for (int i = 0; i < n; i++) { // each col
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        for (int i = 0; i < n; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};

class Solution {
public:
    void rotate(vector<vector<int>>& m) {
        int n = m.size();
        
        for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - i - 1; j++) {
                
                int r = i, c = j;
                int tmp = m[r][c];
                do {
                    int nr = c;
                    int nc = n - 1 - r;
                    swap(tmp, m[nr][nc]);
                    r = nr;
                    c = nc;
                } while (r != i || c != j);
            }
        }
    }
};
