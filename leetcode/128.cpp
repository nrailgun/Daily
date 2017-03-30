// Not strictly O(n), but it works. Anyway, using unionfind seems a bit overkilling.

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
	int longestConsecutive(vector<int> &nums) {
		int n = nums.size();
		unordered_map<int, int> n2i;
		UnionFind uf(n);
		for (int i = 0; i < n; i++) {
			n2i[nums[i]] = i;
		}
		for (int i = 0; i < n; i++) {
			if (n2i[nums[i]] != i)
				continue;
			auto it = n2i.find(nums[i] + 1);
			if (it != n2i.end()) {
				uf.Union(i, it->second);
			}
		}
		int maxc = 0;
		for (int i = 0; i < n; i++) {
			maxc = max(maxc, uf.sz[i]);
		}
		return maxc;
	}
};

// Brutal and straight forward, also the best idea.

class Solution {
public:
	int longestConsecutive(vector<int> &nums) {
		int n = nums.size();
		unordered_set<int> set(nums.begin(), nums.end());
		int maxc = 0;
		for (int i = 0; i < n; i++) {
			auto it = set.find(nums[i]);
			if (it == set.end())
				continue;
			int prev = nums[i] - 1;
			while (set.find(prev) != set.end()) set.erase(prev--);
			int next = nums[i] + 1;
			while (set.find(next) != set.end()) set.erase(next++);
			maxc = max(maxc, next - prev - 1);
		}
		return maxc;
	}
};
