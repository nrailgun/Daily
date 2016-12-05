// 不需要 swap，只需要保留 non-zero 即可，后面填 0。
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nums[j++] = nums[i];
            }
        }
        for (; j < nums.size(); j++) {
            nums[j] = 0;
        }
    }
};
