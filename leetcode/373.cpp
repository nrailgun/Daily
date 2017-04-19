class Comparator {
public:
	const vector<int> *v1, *v2;

	Comparator(const vector<int> *v1, const vector<int> *v2) : v1(v1), v2(v2) {
	}

	bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
		return (*v1)[p1.first] + (*v2)[p1.second] > (*v1)[p2.first] + (*v2)[p2.second];
	}
};

class Solution {
public:
	vector<pair<int, int>> kSmallestPairs(vector<int> &v1, vector<int> &v2, int k) {
		vector<pair<int, int>> rv;
		if (v1.size() == 0 || v2.size() == 0)
			return rv;
		k = min<int>(k, v1.size() * v2.size());

		Comparator comp(&v1, &v2);
		priority_queue<pair<int, int>, vector<pair<int, int>>, Comparator> q(comp);
		q.push(make_pair(0, 0));
		set<pair<int, int>> us;

		for (int i = 0; i < k; i++) {
			pair<int, int> p = q.top();
			q.pop();

			rv.push_back(make_pair(v1[p.first], v2[p.second]));

			if (p.first + 1 < v1.size()) {
				p.first++;
				if (us.end() == us.find(p)) {
					us.insert(p);
					q.push(p);
				}
				p.first--;
			}
			if (p.second + 1 < v2.size()) {
				p.second++;
				if (us.end() == us.find(p)) {
					us.insert(p);
					q.push(p);
				}
				p.second--;
			}
		}
		return rv;
	}
};

