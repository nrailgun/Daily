class Solution {
public:
	string solve(const string &s, vector<int> &shist, const vector<int> &thist) {
		string s1 = s;
		if (shist[s.front()] > thist[s.front()]) {
			shist[s.front()]--;
			s1 = solve(s.substr(1, s.size() - 1), shist, thist);
			shist[s.front()]++;
		}
		string s2 = s;
		if (shist[s.back()] > thist[s.back()]) {
			shist[s.back()]--;
			s2 = solve(s.substr(0, s.size() - 1), shist, thist);
			shist[s.back()]++;
		}
		return s1.size() < s2.size() ? s1 : s2;
	}

	string minWindow(string s, string t) {
		vector<int> shist(256, 0), thist(256, 0);
		for (int i = 0; i < s.size(); i++)
			shist[s[i]]++;
		for (int i = 0; i < t.size(); i++)
			thist[t[i]]++;
		for (int i = 0; i < 256; i++)
			if (shist[i] < thist[i])
				return "";
		return solve(s, shist, thist);
	}
};

class Solution {
public:
	string minWindow(string s, string t) {
		int sbeg = 0, send = 0;
		int l = INT_MAX, head = 0;

		int count = 0;
		vector<int> thist(128, 0);
		for (char c : t)
			thist[c]++;

		while (send < s.size()) {
			if (thist[s[send]]-- > 0)
				count++;
			send++;

			while (count == t.size()) {
				if (send - sbeg < l) {
					l = send - sbeg;
					head = sbeg;
				}
				if (thist[s[sbeg]]++ == 0)
					count--;
				sbeg++;
			}
		}
		return l == INT_MAX ? "" : s.substr(head, l);
	}
};
