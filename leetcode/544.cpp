class Solution {
public:
	string findContestMatch(int n) {
		vector<string> sv(n);
		for (int i = 0; i < n; i++) {
			sv[i] = to_string(i + 1);
		}
		return solve(sv);
	}

	string solve(vector<string> &sv) {
		int n = sv.size();
		if (n == 1)
			return sv[0];
		vector<string> newsv(n / 2);
		for (int i = 0; i < n / 2; i++) {
			newsv[i] = "(" + sv[i] + "," + sv[n - 1 - i] + ")";
		}
		return solve(newsv);
	}
};
