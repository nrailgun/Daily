class Solution {
public:
	vector<int> multiply(const vector<int8_t> &num1, const vector<int8_t> &num2) {
		vector<int> resl(num1.size() + num2.size(), 0);
		for (int i = 0; i < num1.size(); i++) {
			int d1 = num1[i];
			for (int j = 0; j < num2.size(); j++) {
				int d2 = num2[j];
				resl[i + j] += d1 * d2;
			}
		}
		int carry = 0;
		for (int i = 0; i < resl.size(); i++) {
			int d3 = resl[i] + carry;
			carry = d3 / 10;
			resl[i] = d3 % 10;
		}
		while (resl.size() > 1 && resl.back() == 0) {
			resl.pop_back();
		}
		return resl;
	}

	static int ch2i(char ch) {
		return ch - '0';
	}

	static char i2ch(int i) {
		return i + '0';
	}

	string multiply(const string &snum1, const string &snum2) {
		vector<int8_t> num1(snum1.size(), 0), num2(snum2.size(), 0);
		transform(snum1.rbegin(), snum1.rend(), num1.begin(), ch2i);
		transform(snum2.rbegin(), snum2.rend(), num2.begin(), ch2i);

		auto num3 = multiply(num1, num2);
		string snum3(num3.size(), '0');
		transform(num3.rbegin(), num3.rend(), snum3.begin(), i2ch);
		return snum3;
	}
};
