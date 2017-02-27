// 简单 fibnacci 数列。
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2)
            return n;
        
        int i = 3;
        int v1 = 1, v2 = 2, v3;
        while (i++ <= n) {
            v3 = v1 + v2;
            v1 = v2;
            v2 = v3;
        }
        return v3;
    }
};
