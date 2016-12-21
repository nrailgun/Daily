// 简单的思路，用符号位记录是否出现过。O(n) 时间，常数空间。
// Discuss 有另一种思路是把元素分正负堆，只检查正的一堆。
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        int example = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                example = nums[i];
                break;
            }
        }
        if (example == -1)
            return 1;

        for (int i = 0; i < n; i++) {
            if (nums[i] <= 0) {
                nums[i] = example;
            }
        }
        
        for (int i = 0; i < n; i++) {
            int v = abs(nums[i]);
            if (v > n || v == 0)
                continue;
            nums[v-1] = -abs(nums[v-1]);
        }
        
        int j;
        for (j = 0; j < n; j++) {
            if (nums[j] > 0)
                return j+1;
        }
        return j+1;
    }
};
