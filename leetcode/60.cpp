// 很难设计 random access 和 random insert/erase 的数据结构，只能用 vector。

class Solution {
public:
	string getPermutation(int n, int k) {
		char buf[32] = { 0 };
		for (int i = 0; i < n; i++) {
			buf[i] = '0' + i + 1;
		}

		int f = 1;
		for (int i = 2; i <= n; i++) {
			f *= i;
		}

		int idx = 0; // 注意 int i = 0; 不会初始化此处的 i，应该是编译器 BUG。
		k--;
		while (idx < n) {
			f /= n - idx;
			int j = idx + k / f;
			char c = buf[j];
			k %= f;

			for (int j2 = j; j2 > idx; j2--) {
				buf[j2] = buf[j2 - 1];
			}
			buf[idx++] = c;
		}
		return buf;
	}
};
