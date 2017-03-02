// 机智利用 c = a + b 且 c % k == 0 则 a % k == b % k 得出 O(n) 解法。
// 注意 k == 0 和 距离大于 2 的题目要求。
// k == 0 是一个巨坑无比的 special case，直接换算法。

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // if n > k
        
        int n = nums.size();
        int presum = 0;
        unordered_map<int, int> mods;
        mods[0] = 0;
        for (int i = 0; i < n; i++) {
            presum += nums[i];
            int mod = presum;
            if (k != 0) { // k == 0 的情况直接破坏了算法假设，只能存储 presum 了，worst case。
                mod %= k;
            }
            auto it = mods.find(mod);
            if (it != mods.end() && i - it->second > 0)
                return true;
            else if (it == mods.end()) // 注意不要 replace
                mods[mod] = i + 1;
        }
        return false;
    }
};
