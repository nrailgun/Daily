class Solution {
public:
    string reverseWords(string s) {
        char *ss = (char *) s.c_str();
        while (*ss) {
            char *pw = strchr(ss, ' ');
            if (pw) {
                reverse(ss, pw);
            } else {
                reverse(ss, (char *) s.c_str() + s.size());
                break;
            }
            while (*pw != 0 && *pw == ' ')
                pw++;
            ss = pw;
        }
        return s;
    }
};
