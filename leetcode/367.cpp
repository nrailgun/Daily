// 注意：使用 long 避免了 lb+1 时候溢出的问题。

class Solution {
public:
    bool isPerfectSquare(int num) {
        long lb = 1, ub = num;
        
        while (lb <= ub) {
            long mid = lb + (ub - lb) / 2;
            long p2 = mid * mid;
            if (p2 == num) {
                return true;
            } else if (p2 < num) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        return false;
    }
};
