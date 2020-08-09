class Solution {
public:
	set<double> solve(const vector<int> &nums, int bi, int ei) {
		set<double> mys;
		if (bi + 1 == ei) {
			mys.insert(nums[bi]);
			return mys;
		}

		for (int i = bi + 1; i < ei; i++) {
			set<double> s1 = solve(nums, bi, i);
			set<double> s2 = solve(nums, i, ei);
			for (double v1 : s1) {
				for (double v2 : s2) {
					double v3;
					v3 = v1 + v2;
					mys.insert(v3);
					v3 = v1 - v2;
					mys.insert(v3);
					v3 = v1 * v2;
					mys.insert(v3);
					v3 = v1 / v2;
					mys.insert(v3);
				}
			}
		}
		return mys;
	}

	bool judgePoint24(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		do {
			set<double> s = solve(nums, 0, 4);
			for (double x : s) {
				if (fabs(x - 24.0) < 0.001) {
					return true;
				}
			}
		} while (next_permutation(nums.begin(), nums.end()));
		return false;
	}
};
