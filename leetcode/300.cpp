// 客官您好，您要的 O(n^2) 解。
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

// O(n logn)
