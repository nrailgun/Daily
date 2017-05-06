// Permutation 和 Combination 可能是最直接的思路，但是不太好实现，鉴于枚举空间小，直接枚举可以方便实现。

class Solution {
public:
    int bit_count(int x) {
        int n = 0;
        while (x) {
            x &= (x - 1);
            n++;
        }
        return n;
    }

    vector<string> readBinaryWatch(int num) {
        vector<string> rv;
        
        for (int h = 0; h < 12; h++) {
            for (int m = 0; m < 60; m++) {
                if (bit_count(h * 64 + m) == num) {
                    char buf[BUFSIZ];
                    snprintf(buf, BUFSIZ, "%d:%02d", h, m);
                    rv.push_back(string(buf));
                }
            }
        }
        return rv;
    }
};
