class Solution {
public:
    bool wordPattern(string pattern, string str) {
        string c2s[256];
        unordered_map<string, char> s2c;
        
        stringstream st;
        st << str;
        int i = 0;
        while (i < pattern.size() && !st.eof()) {
            char ch = pattern[i];
            string s;
            st >> s;
            if (c2s[ch] != "" && c2s[ch] != s)
                return false;
            unordered_map<string, char>::const_iterator it = s2c.find(s);
            if (it != s2c.end() && it->second != ch)
                return false;
            
            c2s[ch] = s;
            s2c[s] = ch;
            i++;
        }
        return i == pattern.size() && st.eof();
    }
};
