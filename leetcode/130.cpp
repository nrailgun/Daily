// Can also be solved in DFS.

class UnionFind {
public:
	vector<int> id;
	vector<int> sz;
	int ncomponent;

	UnionFind(int n) : id(n), sz(n), ncomponent(n) {
		for (int i = 0; i < n; i++) {
			id[i] = i;
			sz[i] = 1;
		}
	}

	int Find(int p) {
		while (p != id[p]) {
			id[p] = id[id[p]];
			p = id[p];
		}
		return p;
	}

	bool Union(int p, int q) {
		int i = Find(p), j = Find(q);
		if (i == j)
			return false;
		ncomponent--;
		if (sz[i] < sz[j]) {
			id[i] = j;
			sz[j] += sz[i];
		}
		else {
			id[j] = i;
			sz[i] += sz[j];
		}
		return true;
	}

	bool Connected(int p, int q) {
		int i = Find(p), j = Find(q);
		return i == j;
	}
};

class Solution {
public:
	int m, n;

	void solve(vector<vector<char>>& board) {
		m = board.size();
		if (!m)
			return;
		n = board[0].size();

		UnionFind uf(m * n + 1);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] != 'O')
					continue;
				int idx = i * n + j;
				if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
					uf.Union(idx, n * m);
				}
				if (i + 1 < m && board[i + 1][j] == 'O') {
					uf.Union(idx, idx + n);
				}
				if (j + 1 < n && board[i][j + 1] == 'O') {
					uf.Union(idx, idx + 1);
				}
			}
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] != 'O')
					continue;
				int idx = i * n + j;
				if (!uf.Connected(idx, n * m)) {
					board[i][j] = 'X';
				}
			}
		}
	}
};
