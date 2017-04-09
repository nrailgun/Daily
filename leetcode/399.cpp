// 简单的最短路算法而已，结合一点其他算法。

class Solution {
public:
	unordered_map<string, int> v2i;
	vector<list<pair<int, double>>> edges; // a / b = v
	vector<bool> visited;

	double solve(int a, int b) {
		if (a == b)
			return 1;
		visited[a] = true;

		double rv = INT_MIN;
		const list<pair<int, double>> &l = edges[a];
		for (auto it = l.begin(); it != l.end(); ++it) {
			if (visited[it->first])
				continue;
			double v = solve(it->first, b);
			if (v != INT_MIN) {
				rv = it->second * v;
				goto out;
			}
		}
	out:
		visited[a] = false;
		return rv;
	}

	vector<double> calcEquation(
		vector<pair<string, string>> equations,
		vector<double>& values,
		vector<pair<string, string>> queries)
	{
		v2i.clear();
		for (int i = 0; i < equations.size(); i++) {
			string v1 = equations[i].first;
			if (v2i.find(v1) == v2i.end()) {
				v2i.insert(make_pair(v1, v2i.size()));
			}

			string v2 = equations[i].second;
			if (v2i.find(v2) == v2i.end()) {
				v2i.insert(make_pair(v2, v2i.size()));
			}

			int i1 = v2i[v1], i2 = v2i[v2];
			if (i1 >= edges.size() || i2 >= edges.size()) {
				edges.resize(1 + max(i1, i2));
			}
			edges[i1].push_back(make_pair(i2, values[i]));
			edges[i2].push_back(make_pair(i1, 1 / values[i]));
		}

		visited.resize(edges.size());
		fill(visited.begin(), visited.end(), false);

		vector<double> rv;
		for (int i = 0; i < queries.size(); i++) {
			string v1 = queries[i].first, v2 = queries[i].second;
			if (v2i.end() == v2i.find(v1) || v2i.end() == v2i.find(v2)) {
				rv.push_back(-1.0);
				continue;
			}

			int i1 = v2i[v1];
			int i2 = v2i[v2];
			double v = solve(i1, i2);
			rv.push_back(v == INT_MIN ? -1.0 : v);
		}
		return rv;
	}
};
