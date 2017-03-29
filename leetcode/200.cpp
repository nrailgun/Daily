// Reviewed UnionFind.

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

	void Union(int p, int q) {
		int i = Find(p), j = Find(q);
		if (i != j) {
			ncomponent--;
			if (sz[i] < sz[j]) {
				id[i] = j;
				sz[j] += sz[i];
			}
			else {
				id[j] = i;
				sz[i] += sz[j];
			}
		}
	}
};

class Solution {
public:
	int numIslands(vector<vector<char>> &grid) {
		int m = grid.size();
		if (!m)
			return 0;
		int n = grid[0].size();

		UnionFind uf(m * n + 1);

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] != '1')
					uf.Union(i * n + j, m * n);
				else {
					if (j + 1 < n && grid[i][j + 1] == '1')
						uf.Union(i * n + j + 1, i * n + j);
					if (i + 1 < m && grid[i + 1][j] == '1')
						uf.Union(i * n + j + n, i * n + j);
				}
			}
		}
		return uf.ncomponent - 1;
	}
};
