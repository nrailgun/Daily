// 只不过是 LIS 问题的 special case。
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        vector<int> v;
        
        for (int i = 0; i < nums.size(); i++) {
            auto it = lower_bound(v.begin(), v.end(), nums[i]);
            if (it == v.end()) {
                v.push_back(nums[i]);
                if (v.size() == 3)
                    return true;
            } else
                *it = nums[i];
        }
        return false;
    }
};

// 不过可以针对 size == 3 进行优化，不需要 bsearch。
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int small = INT_MAX, big = INT_MAX;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= small)
                small = nums[i];
            else if (nums[i] <= big)
                big = nums[i];
            else
                return true;
        }
        return false;
    }
};
