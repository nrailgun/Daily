// 题目虽然是 HARD，其实很简单，但是套路多，题目描述不清楚有误导性。

class Solution {
public:
	bool is_scramble(const string &s1, int i1, const string &s2, int i2, int l) {
		if (l == 1)
			return s1[i1] == s2[i2];

		for (int l2 = 1; l2 < l; l2++) {
			if (is_scramble(s1, i1, s2, i2, l2)
				&& is_scramble(s1, i1 + l2, s2, i2 + l2, l - l2))
			{
				return true;
			}
			if (is_scramble(s1, i1, s2, i2 + l - l2, l2)
				&& is_scramble(s1, i1 + l2, s2, i2, l - l2))
			{
				return true;
			}
		}
		return false;
	}

	bool isScramble(const string &s1, const string &s2) {
		if (s1.size() != s2.size())
			return false;
		return is_scramble(s1, 0, s2, 0, s1.size());
	}
};

// Pruning to avoid Timeout.

class Solution {
public:
	bool is_scramble(const string &s1, int i1, const string &s2, int i2, int l) {
		if (l == 1)
			return s1[i1] == s2[i2];

		// 剪枝1
		if (!strncmp(s1.c_str() + i1, s2.c_str() + i2, l))
			return true;

		// 剪枝2：这个剪枝超级无敌重要。
		int counts1[26] = { 0 };
		int counts2[26] = { 0 };
		for (int i = 0; i < l; i++) {
			counts1[s1[i1 + i] - 'a']++;
			counts2[s2[i2 + i] - 'a']++;
		}
		for (int i = 0; i < 26; i++) {
			if (counts1[i] != counts2[i])
				return false;
		}

		for (int l2 = 1; l2 < l; l2++) {
			if (is_scramble(s1, i1, s2, i2, l2)
				&& is_scramble(s1, i1 + l2, s2, i2 + l2, l - l2))
			{
				return true;
			}
			if (is_scramble(s1, i1, s2, i2 + l - l2, l2)
				&& is_scramble(s1, i1 + l2, s2, i2, l - l2))
			{
				return true;
			}
		}
		return false;
	}

	bool isScramble(const string &s1, const string &s2) {
		if (s1.size() != s2.size())
			return false;
		return is_scramble(s1, 0, s2, 0, s1.size());
	}
};
