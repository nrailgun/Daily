// Very simple DP.
class Solution {
public:
    int rob(vector<int>& nums) {
        int N = nums.size();
        if (!N)
            return 0;
        
        int y = nums[0], n = 0;
        for (int i = 1; i < N; i++) {
            int oy = y, on = n;
            y = nums[i] + on;
            n = max(oy, on);
        }
        return max(y, n);
    }
};
