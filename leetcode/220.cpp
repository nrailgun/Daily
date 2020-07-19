// 这题目主要是考察 bucket 粗略分数据的思想。

class Solution {
public:
	int64_t getbucket(int64_t v, int64_t t) {
		if (v >= 0) {
			return v / t;
		}
		else {
			return (v + 1) / t - 1;
		}
	}

	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int _t) {
		int n = nums.size();
		if (n == 0) {
			return false;
		}
		if (_t < 0) {
			return false;
		}

		int64_t t = (int64_t) _t + 1;
		unordered_map<int64_t, int64_t> buckets;
		for (int i = 0; i < n; i++) {
			int64_t b = getbucket(nums[i], t);
			if (buckets.find(b) != buckets.end()) {
				return true;
			}
			{
				unordered_map<int64_t, int64_t>::iterator it = buckets.find(b - 1);
				if (it != buckets.end()) {
					if (abs(nums[i] - it->second) < t)
						return true;
				}
			}
			{
				unordered_map<int64_t, int64_t>::iterator it = buckets.find(b + 1);
				if (it != buckets.end()) {
					if (abs(nums[i] - it->second) < t)
						return true;
				}
			}
			buckets.insert(make_pair(b, nums[i]));
			if (i >= k) {
				buckets.erase(getbucket(nums[i - k], t));
			}
		}
		return false;
	}
};
