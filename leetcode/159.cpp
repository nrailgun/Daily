// 利用 minimum window substring 可以在 O(n) 复杂度轻松解该题。

class Solution {
public:
	int lengthOfLongestSubstringTwoDistinct(string s) {
		int sbeg = 0, send = 0;
		int l = 0, head = 0;
		map<char, int> cc;

		while (send < s.size()) {
			while (send <= s.size() && cc.size() <= 2) {
				if (send - sbeg > l) {
					head = sbeg;
					l = send - sbeg;
				}
				cc[s[send++]]++;
			}
			while (cc.size() > 2) {
				if (--cc[s[sbeg++]] == 0) {
					cc.erase(s[sbeg - 1]);
				}
			}
		}
		return l;
	}
};
