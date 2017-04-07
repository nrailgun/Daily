// 1000 leads to Runtime limit.

class Solution {
public:
	vector<bool> uglys;
	vector<int> nth_ugly;

	Solution() : uglys(6, true) { // [1][2][3][4][5] = true
		nth_ugly.push_back(1);
	}

	void set_flag(int i) {
		while (uglys.size() <= i) {
			uglys.resize(uglys.size() * 2);
		}
		uglys[i] = true;
	}

	int nthUglyNumber(int n) {
		if (n - 1 < nth_ugly.size())
			return nth_ugly[n - 1];

		for (int i = nth_ugly.back() + 1; nth_ugly.size() < n; i++) {
			if (uglys[i]) {
				nth_ugly.push_back(i);
				set_flag(i * 2);
				set_flag(i * 3);
				set_flag(i * 5);
			}
		}
		return nth_ugly.back();
	}
};

