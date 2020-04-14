// 并不困难，但写起来，字符串操作事实上很容易出错。

class Solution {
public:
	string reverseWords(string s) {
		int n = s.size();
		int i = 0, j;
		for (j = 0; j < n; ) {
			if (s[j] != ' ')
				s[i++] = s[j++];
			else {
				while (j < n && s[j] == ' ')
					j++;
				if (i != 0 && j < n)
					s[i++] = ' ';
			}
		}
		n = i;
		s.resize(n);
		reverse(s.begin(), s.end());

		for (i = 0; i < n; ) {
			j = 1;
			while (i + j < n && s[i + j] != ' ')
				j++;
			reverse(s.begin() + i, s.begin() + i + j);
			i += ++j;
		}
		return s;
	}
};
