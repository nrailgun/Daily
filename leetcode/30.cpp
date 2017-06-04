// A very very Naive and Straight forward solution.
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& ws) {
		unordered_map<string, int> wcnt;
		for (auto w : ws)
			wcnt[w]++;
		int n = s.size();
		int nw = ws.size(), wl = ws[0].size();
		vector<int> rv;
		for (int i = 0; i <= n - nw * wl; i++) {
			unordered_map<string, int> cnt;
			int j;
			for (j = 0; j < nw; j++) {
				string subs = s.substr(i + j * wl, wl);
				if (++cnt[subs] > wcnt[subs])
					break;
			}
			if (j == nw)
				rv.push_back(i);
		}
		return rv;
	}
};
