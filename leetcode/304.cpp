// Simple DP solution.

class NumMatrix {
public:
	vector<vector<int>> M;

	NumMatrix(const vector<vector<int>> &matrix) : M(matrix) {
		int m = M.size();
		if (!m)
			return;
		int n = M[0].size();
		
		for (int i = 1; i < n; i++) {
			M[0][i] += M[0][i - 1];
		}
		for (int i = 1; i < m; i++) {
			M[i][0] += M[i - 1][0];
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				M[i][j] += M[i - 1][j] + M[i][j - 1] - M[i - 1][j - 1];
			}
		}
	}

	int sumRegion(int r1, int c1, int r2, int c2) {
		return M[r2][c2]
			- (c1 > 0 ? M[r2][c1 - 1] : 0)
			- (r1 > 0 ? M[r1 - 1][c2] : 0)
			+ (r1 > 0 && c1 > 0 ? M[r1 - 1][c1 - 1] : 0);
	}
};
