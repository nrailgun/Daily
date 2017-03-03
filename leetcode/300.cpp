// 客官您好，您要的 O(n^2) 解。
// 虽然 DP 思想更加复杂一些，但是 DP 解法不一定是最好的解法。有些富有灵性的解法可以超过 DP。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (!n)
            return 0;
        vector<int> lens(n, 1);
        for (int i = 1; i < n; i++) {
            int maxl = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    maxl = max(maxl, lens[j]+1);
                }
            }
            lens[i] = maxl;
        }
        return *max_element(lens.begin(), lens.end());
    }
};

// 经典问题 LIS（Longest Increasing Subsequence） 的复杂度为 O(n logn)。
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (!n)
            return 0;
        vector<int> res;
        
        for (int i = 0; i < n; i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
            if (it == res.end())
                res.push_back(nums[i]);
            else
                *it = nums[i];
        }
        return res.size();
    }
};
