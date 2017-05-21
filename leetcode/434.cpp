class Solution {
public:
    int countSegments(string s) {
        int cnt = 0;
        int i = 0;
        
        while (i < s.size()) {
            while (i < s.size() && isspace(s[i]))
                i++;
            if (i == s.size())
                return cnt;
            cnt++;
            while (i < s.size() && !isspace(s[i]))
                i++;
        }
        return cnt;
    }
};
