// 就是二分查找而已。
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int *a = nums.data();
        int idx;
        
        if (n == 1 || a[n-1] > a[0])
            idx = 0;
        else {
            int lb = 0, ub = n - 1;
            while (lb <= ub) {
                int mid = (lb + ub) / 2;
                if ((mid == n - 1 || a[mid] < a[mid+1]) && (mid == 0 || a[mid] < a[mid-1])) {
                    idx = mid;
                    break;
                } else if (a[mid] >= a[0]) {
                    lb = mid + 1;
                } else {
                    ub = mid - 1;
                }
            }
        }
        return nums[idx];
    }
};
