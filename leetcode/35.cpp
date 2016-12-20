class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int *p = nums.data();
        int n = nums.size();
        int l = 0, r = n - 1;
        
        while (l <= r) {
            int mid = (l+r)/2;
            
            // 这里有个 trick。可以减少一次判断。
            if (p[mid]==target){
                return mid;
            } else if (p[mid]>target) {
                r=mid-1;
            } else {
                l=mid+1;
            }
        }
        return l;
    }
};
