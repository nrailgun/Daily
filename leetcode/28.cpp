// 按理应该使用 KMP 算法，不过 naive pattern searching 居然也能 defeat 90%。
class Solution {
public:
    int strStr(string s1, string s2) {
        for (int i = 0; i < (int) s1.size() - (int) s2.size() + 1; i++) {
            bool match = true;
            for (int j = 0; j < s2.size(); j++) {
                if (s1[i+j] != s2[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                return i;
        }
        return -1;
    }
};

// KMP 算法是比较难以理解的算法，需要多理解一遍。

class Solution {
public:
    vector<int> compute_lps(const string &pat) {
        int M = pat.size();
        vector<int> lps(M, 0);
        
        int len = 0, i = 1;
        lps[0] = 0;
        while (i < M) {
            if (pat[i] == pat[len]) {
                lps[i++] = ++len;
            } else {
                if (len != 0)
                    len = lps[len - 1];
                else
                    lps[i++] = 0;
            }
        }
        return lps;
    }
    
    int kmp_search(const string &txt, const string &pat) {
        if (pat == "")
            return 0;
        vector<int> lps = compute_lps(pat);
        
        int N = txt.size(), M = pat.size();
        int i = 0, j = 0;
        while (i < N) {
            if (txt[i] == pat[j]) {
                i++;
                j++;
            }
            if (j == M)
                return i - j;

            if (i < N && txt[i] != pat[j]) {
                if (j == 0)
                    i++;
                else
                    j = lps[j - 1];
            }
        }
        return -1;
    }
    
    int strStr(string txt, string pat) {
        return kmp_search(txt, pat);
    }
};
