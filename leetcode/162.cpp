class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        
        int lb = 0, ub = n - 1;
        while (lb <= ub) {
            int mid = (lb + ub) / 2;
            int v1 = mid == 0 ? INT_MIN : nums[mid-1];
            int v2 = nums[mid];
            int v3 = mid == n - 1 ? INT_MIN : nums[mid+1];
            
            if (v2 >= v1 && v2 >= v3)
                return mid;
            else if (v1 <= v2 && v2 <= v3)
                lb = mid + 1;
            else
                ub = mid - 1;
        }
        return -1;
    }
};
