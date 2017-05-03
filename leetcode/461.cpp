class Solution {
public:
    int hammingDistance(int x, int y) {
        int d = 0;
        
        while (x || y) {
            if ((x ^ y) & 1) {
                d++;
            }
            x >>= 1;
            y >>= 1;
        }
        return d;
    }
};
