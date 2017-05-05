class Solution {
public:
    int titleToNumber(const string &s) {
        int v = 0;
        int base = 1;
        
        for (int i = int(s.size()) - 1; i >= 0; i--) {
            v += base * (s[i] - 'A' + 1);
            base *= 26;
        }
        
        return v;
    }
};
