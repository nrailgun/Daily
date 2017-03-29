class Solution {
public:
	vector<char> from, to;

	Solution() : from(5), to(5) {
		from[0] = '0'; to[0] = '0';
		from[1] = '1'; to[1] = '1';
		from[2] = '6'; to[2] = '9';
		from[3] = '8'; to[3] = '8';
		from[4] = '9'; to[4] = '6';
	}

	vector<string> findStrobogrammatic(int n, bool first = true) {
		if (n <= 0)
			return vector<string>({ "" });
		else if (n == 1)
			return vector<string>({ "0", "1", "8" });
		
		vector<string> sv = findStrobogrammatic(n - 2, false);
		vector<string> rv;
		for (int i = first ? 1 : 0; i < 5; i++) {
			string s(n, 0);
			s[0] = from[i];
			s[n - 1] = to[i];
			for (string subs : sv) {
				strncpy(const_cast<char*>(s.c_str() + 1), subs.c_str(), subs.size());
				rv.push_back(s);
			}
		}
		return rv;
	}
};
