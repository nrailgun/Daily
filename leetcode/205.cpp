// 确保两两映射。
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        char m[256] = { 0 };
        bool b[256] = { false };
        
        for (int i = 0; i < s.size(); i++) {
            int ch = s[i];
            if (m[ch] == 0) {
                if ( b[t[i]] )
                    return false;
                b[t[i]] = true;
                m[ch] = t[i];
            }
            else if (m[ch] != t[i])
                return false;
        }
        return true;
    }
};
