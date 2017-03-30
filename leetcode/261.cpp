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
	bool validTree(int n, vector<pair<int, int>> &edges) {
		UnionFind uf(n);
		for (int i = 0; i < edges.size(); i++) {
			if (!uf.Union(edges[i].first, edges[i].second))
				return false;
		}
		return uf.ncomponent == 1;
	}
};
