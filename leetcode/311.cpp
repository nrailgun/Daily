// Regular matrix multiplication isn't good enough for sparse matrixs.
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size(), p = B.size(), n = B[0].size();
        vector<vector<int>> C(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < p; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }
};

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size(), p = B.size(), n = B[0].size();
        vector<vector<int>> C(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            for (int k = 0; k < p; k++) {
                if (A[i][k]) { // Trick
                    for (int j = 0; j < n; j++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
        return C;
    }
};
