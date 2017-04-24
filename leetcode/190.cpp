class Solution {
public:
	unsigned reverseBits(unsigned n) {
		int v = 0;
		for (int i = 0; i < 32; i++) {
			v |= (1 & (n >> (31 - i))) << i;
		}
		return v;
	}
};

// 可以先交换 0-15 和 16-31，再交换 0-7,8-15,16-23,24-32，以此类推。
