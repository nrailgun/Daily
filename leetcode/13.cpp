// 罗马计数比较费解。

class Solution {
public:
    int toint(char c) {
        switch (c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        }
    }
    
    int romanToInt(string s) {
        int rv = 0;
        
        for (int i = 0; i < s.size()-1; i++) {
            int v1 = toint(s[i]);
            int v2 = toint(s[i+1]);
            if (v1 < v2)
                rv -= v1;
            else
                rv += v1;
        }
        rv += toint(s[s.size()-1]);
        return rv;
    }
};
