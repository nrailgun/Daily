class Solution {
public:
	int rangeBitwiseAnd(int m, int n) {
		int a = m ^ n;
		int msbpos = 0;
		while (a) {
			msbpos++;
			a >>= 1;
		}
		unsigned int mask = 0xffffffff;
		for (int i = 0; i < msbpos; i++) {
			mask <<= 1;
		}
		return m & mask;
	}
};
