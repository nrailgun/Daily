class Solution {
public:
    int findMin(vector<int>& nums) {
        int lb = 0, ub = nums.size() - 1;
        
        while (lb < ub) {
            if (lb + 1 == ub) {
                return min(nums[lb], nums[ub]);
            }
            
            if (nums[lb] < nums[ub])
                return nums[lb];
            if (nums[lb] == nums[ub]) {
                ub--;
                continue;
            }

            int mid = lb + (ub - lb) / 2;
            if (nums[lb] == nums[mid]) {
                lb++;
            } else if (nums[lb] < nums[mid]) {
                lb = mid + 1;
            } else {
                ub = mid;
            }
        }
        return nums[lb];
    }
};
