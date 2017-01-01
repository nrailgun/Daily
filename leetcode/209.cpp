// 滑动窗口，不停滑动，取得各个不同的段。
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int *a = nums.data();
        int n = nums.size();
        if (n == 0)
            return 0;
        
        int lb = 0, ub = 0;
        int ts = a[0];
        int minlen = INT_MAX;
        while (ub < n) {
            if (ts < s) {
                if (++ub < n)
                    ts += nums[ub];
            } else {
                minlen = min(minlen, ub - lb + 1);
                ts -= a[lb++];
            }
        }
        
        if (minlen == INT_MAX)
            return 0;
        else
            return minlen;
    }
};
