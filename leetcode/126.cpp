// Can't memorize solution, because it's hard to encode 'visited' state. Naive DFS leads
// to LTE.

class Solution {
public:
	int n;
	vector<vector<bool>> adjacent;
	typedef vector<int> Path;
	typedef vector<Path> Paths;
	vector<bool> visited;

	bool is_adjacent(const string &a, const string &b) {
		int cnt = 0;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] != b[i] && ++cnt > 1)
				return false;
		}
		return true;
	}

	pair<int, Paths> solve(int ci, int ei) {
		if (ci == ei) {
			Paths paths;
			paths.push_back(Path(1, ci));
			return make_pair(1, paths);
		}

		visited[ci] = true;
		Paths paths;
		int l = INT_MAX;
		for (int i = 0; i < n; i++) {
			if (visited[i] || !adjacent[ci][i])
				continue;

			pair<int, Paths> i2ei = solve(i, ei);
			int curl = i2ei.first;
			const Paths &curpaths = i2ei.second;
			if (curl == INT_MAX)
				continue;
			if (curl < l) {
				l = curl;
				paths.clear();
			}
			if (curl <= l) {
				for (int j = 0; j < curpaths.size(); j++) {
					Path path;
					path.push_back(ci);
					path.insert(path.end(), curpaths[j].begin(), curpaths[j].end());
					paths.push_back(path);
				}
			}
		}
		visited[ci] = false;
		return make_pair(l == INT_MAX ? INT_MAX : l + 1, paths);
	}

	vector<vector<string>> findLadders(const string &bw, const string &ew, vector<string> wl) {
		int bi = -1, ei = -1;
		for (int i = 0; i < wl.size(); i++) {
			if (bw == wl[i])
				bi = i;
			if (ew == wl[i])
				ei = i;
		}
		if (ei == -1)
			return vector<vector<string>>();
		if (bi == -1) {
			wl.insert(wl.begin(), bw);
			bi = 0;
			ei++;
		}
		
		n = wl.size();
		adjacent = vector<vector<bool>>(n, vector<bool>(n, false));
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (is_adjacent(wl[i], wl[j]))
					adjacent[i][j] = adjacent[j][i] = true;
			}
		}
		visited = vector<bool>(n, false);

		vector<vector<string>> rv;
		pair<int, Paths> solve_rv = solve(bi, ei);
		const Paths &paths = solve_rv.second;
		for (int i = 0; i < paths.size(); i++) {
			const Path &path = paths[i];
			vector<string> spath(1, bw);
			for (int j = 1; j < path.size(); j++) {
				spath.push_back(wl[path[j]]);
			}
			rv.push_back(spath);
		}
		return rv;
	}
};
