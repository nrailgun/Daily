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
};

class Solution {
public:
	int m, n;

	inline int rc2i(int r, int c) {
		return r * n + c;
	}

	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
		vector<int> rv;
		this->m = m;
		this->n = n;

		UnionFind uf(m * n + 1);
		vector<vector<bool>> M(m, vector<bool>(n, false));
		for (int i = 0; i < positions.size(); i++) {
			const pair<int, int> &posi = positions[i];
			int r = posi.first;
			int c = posi.second;
			int idx = rc2i(r, c);
			M[r][c] = true;

			if (r - 1 >= 0 && M[r - 1][c]) {
				uf.Union(idx, rc2i(r - 1, c));
			}
			if (r + 1 < m && M[r + 1][c]) {
				uf.Union(idx, rc2i(r + 1, c));
			}
			if (c - 1 >= 0 && M[r][c - 1]) {
				uf.Union(idx, rc2i(r, c - 1));
			}
			if (c + 1 < n && M[r][c + 1]) {
				uf.Union(idx, rc2i(r, c + 1));
			}
			rv.push_back(uf.ncomponent - m * n + i);
		}
		return rv;
	}
};
