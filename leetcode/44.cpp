// Wildcard matching.

class Solution {
public:
    bool isMatch(const string &_s, const string &_p) {
        const char *s = _s.c_str(), *p = _p.c_str();
        const char *star = NULL, *ss = NULL;
        
        while (*s) {
            if (*p == '?' || *s == *p) {
                s++;
                p++;
                continue;
            }
            
            if (*p == '*') {
                star = p;
                ss = s;
                p++;
                continue;
            }
            
            if (star) {
                p = star + 1;
                s = ++ss;
            }
            else
                return false;
        }
        
        while (*p == '*')
            p++;
        return !(*p);
    }
};
