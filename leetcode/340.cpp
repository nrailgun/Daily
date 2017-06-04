class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int sbeg = 0, send = 0;
		int l = 0, head = 0;
		map<char, int> cc;

		while (send < s.size()) {
			while (send <= s.size() && cc.size() <= k) {
				if (send - sbeg > l) {
					head = sbeg;
					l = send - sbeg;
				}
				cc[s[send++]]++;
			}
			while (cc.size() > k) {
				if (--cc[s[sbeg++]] == 0) {
					cc.erase(s[sbeg - 1]);
				}
			}
		}
		return l;
    }
};
