class Solution {
public:
    int mySqrt(int x) {
        if (x <= 0)
            return x;
        
        int lb = 1, ub = x;
        int ans;
        while (lb <= ub) {
            int mid = lb + (ub - lb) / 2;
            
            if (mid <= x / mid) {
                lb = mid + 1;
                ans = mid;
            } else
                ub = mid - 1;
        }
        return ans;
    }
};
