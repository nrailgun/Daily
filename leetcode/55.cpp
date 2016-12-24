// 记录每个点能走到的最远位置，然后一直向前走，更新最远位置。
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int reach = 0;
        for (int i = 0; i < n && i <= reach; i++) {
            reach = max(i + nums[i], reach);
        }
        return reach >= n - 1;
    }
};
