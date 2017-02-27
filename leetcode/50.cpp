class Solution {
public:
    double myPow(double x, int n) {
        long long int p = n;
        if (n < 0) {
            x = 1 / x;
            p = -p;
        }
        
        double rv = 1;
        while (p) {
            if ( p & 1 ) // p % 2
                rv *= x;
            x *= x;
            p >>= 1; // p /= 2
        }
        return rv;
    }
};
