class Solution {
public:
    string reverseString(const string &s) {
        const char *ss = s.c_str();
        int n = s.size();
        char *c = new char[n + 1];
        c[s.size()] = '\0';
        for (int i = 0; i < s.size(); i++) {
            c[i] = ss[n - 1 - i];
        }
        return string(c);
    }
};
