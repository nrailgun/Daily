// Simple DP.

class Solution {
public:
    int numWays(int n, int k) {
        if (!n)
            return 0;
            
        int same = 0, diff = k;
        for (int i = 1; i < n; i++) {
            int osame = same, odiff = diff;
            same = odiff;
            diff = (osame + odiff) * (k-1);
        }
        return same + diff;
    }
};
