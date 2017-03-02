// 计算 KMP 的 lps 即可。我真是富有想象力啊。。。
class Solution {
public:
    vector<int> compute_lps(const string &s) {
        int m = s.size();
        vector<int> lps(m, 0);
        
        int i = 1, len = 0;
        while (i < m) {
            if (s[i] == s[len]) {
                lps[i++] = ++len;
            } else {
                if (len == 0) {
                    lps[i++] = 0;
                } else {
                    len = lps[len - 1];
                }
            }
        }
        return lps;
    }

    bool repeatedSubstringPattern(string s) {
        if (s=="")
            return false;
        
        vector<int> lps = compute_lps(s);
        int len = lps.back();
        int pl = s.size() - len;
        return len != 0 && len % pl == 0;
    }
};
