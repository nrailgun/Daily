// According to "increasing" property, the path we visited couldn't be visit again since the value of the grid we
// visited must be less than the value of current grid.

class Solution {
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int m = matrix.size();
		if (m == 0)
			return 0;
		int n = matrix[0].size();
		vector<vector<int>> memo(m, vector<int>(n, 0));
		
		int maxlen = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				int len = solve(matrix, i, j, memo);
				maxlen = max(maxlen, len);
			}
		}
		return maxlen;
	}

	int solve(vector<vector<int>> &M, int r, int c, vector<vector<int>> &memo) {
		if (memo[r][c] != 0)
			return memo[r][c];
		
		int m = M.size();
		int n = M[0].size();
		int len, maxlen = 0;
		int nextr, nextc;

		nextr = r - 1;
		nextc = c;
		if (nextr >= 0 && nextr < m && nextc >= 0 && nextc < n && M[nextr][nextc] > M[r][c]) {
			len = solve(M, nextr, nextc, memo);
			maxlen = max(maxlen, len);
		}

		nextr = r;
		nextc = c - 1;
		if (nextr >= 0 && nextr < m && nextc >= 0 && nextc < n && M[nextr][nextc] > M[r][c]) {
			len = solve(M, nextr, nextc, memo);
			maxlen = max(maxlen, len);
		}

		nextr = r;
		nextc = c + 1;
		if (nextr >= 0 && nextr < m && nextc >= 0 && nextc < n && M[nextr][nextc] > M[r][c]) {
			len = solve(M, nextr, nextc, memo);
			maxlen = max(maxlen, len);
		}

		nextr = r + 1;
		nextc = c;
		if (nextr >= 0 && nextr < m && nextc >= 0 && nextc < n && M[nextr][nextc] > M[r][c]) {
			len = solve(M, nextr, nextc, memo);
			maxlen = max(maxlen, len);
		}

		return memo[r][c] = (maxlen + 1);
	}
};
