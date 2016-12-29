class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        int last = INT_MIN;
        int last_cnt = 0;
        
        int i, j = 0;
        for (i = 0; i < n; i++) {
            if (nums[i] != last || last_cnt == 0) {
                last = nums[i];
                last_cnt = 1;
                nums[j++] = last;
            } else if (last_cnt == 1) {
                last_cnt = 2;
                nums[j++] = last;
            }
        }
        return j;
    }
};
