class Solution {
public:
    int rob(const vector<int> &nums, int from, int to) {
        int y = nums[from], n = 0;
        
        for (int i = from + 1; i < to; i++) {
            int oy = y, on = n;
            y = max(oy, nums[i] + on);
            n = max(oy, on);
        }
        return max(y, n);
    }

    int rob(vector<int>& nums) {
        int N = nums.size();
        if (!N)
            return 0;
        if (N == 1)
            return nums[0];
            
        return max(rob(nums, 0, nums.size() - 1), rob(nums, 1, nums.size()));
    }
};
