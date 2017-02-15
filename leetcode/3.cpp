// 只有 26 个 key，所以其实 vector 存速度会更快。
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char, int> m;
        const int n = s.size();
        if (n == 0)
            return 0;
        const char *ss = s.c_str();
        
        int sp = 0;
        int ml = 1;
        m[ss[0]] = 0;
        for (int i = 1; i < n; i++) {
            map<char, int>::const_iterator it = m.find(ss[i]);
            if (it != m.end() && it->second >= sp) {
                sp = it->second + 1;
            }
            m[ss[i]] = i;
            ml = max(ml, 1 + i - sp);
        }
        return ml;
    }
};
