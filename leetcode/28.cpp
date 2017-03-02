// 按理应该使用 KMP 算法，不过 naive pattern searching 居然也能 defeat 90%。
class Solution {
public:

    vector<int> compute_lps(const string &pat) {
        int m = pat.size();
        vector<int> lps(m, 0);
        
        int i = 1, len = 0;
        while (i < m) {
            if (pat[i] == pat[len]) {
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

    int kmp(const string &txt, const string &pat) {
        int n = txt.size(), m = pat.size();
        vector<int> lps = compute_lps(pat);
        
        int i = 0, j = 0;
        while (i < n) {
            if (txt[i] == pat[j]) {
                i++;
                if (++j == m) {
                    // j = lps[j - 1] if we want all matches
                    return i - m;
                }
            } else {
                if (j == 0)
                    i++;
                else
                    j = lps[j - 1];
            }
        }
        return -1;
    }
    
    int strStr(string txt, string pat) {
        if (pat == "")
            return 0;
        return kmp(txt, pat);
    }
};
