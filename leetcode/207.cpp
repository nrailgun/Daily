// By topological sort.

class Solution {
public:
	bool canFinish(int n, vector<vector<int>> &pres) {
		if (n == 0) {
			return true;
		}

		vector<vector<int>> premat(n, vector<int>());
		vector<int> inds(n, 0);
		for (const auto &pre : pres) {
			int a = pre[0];
			int b = pre[1]; // b goes before a
			inds[a]++;
			premat[b].push_back(a);
		}

		queue<int> zins;
		for (int i = 0; i < n; i++) {
			if (inds[i] == 0) {
				zins.push(i);
			}
		}
		int ok = 0;
		while (!zins.empty()) {
			int a = zins.front();
			zins.pop();
			ok++;

			for (int b : premat[a]) {
				if (--inds[b] == 0) {
					zins.push(b);
				}
			}
		}
		return ok == n;
	}
};
