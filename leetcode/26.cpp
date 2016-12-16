class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
            
        int i, j;
        for (i = 1, j = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i-1]) {
                nums[j++] = nums[i];
            }
        }
        return j;
    }
};
