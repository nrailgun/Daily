class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> nbits(n+1);
        int sz = 1, sz2 = 2, i = 1;
        while (i <= n) {
            nbits[i] = nbits[i - sz] + 1;
            if (++i == sz2) {
                sz *= 2;
                sz2 *= 2;
            }
        }
        return nbits;
    }
};
