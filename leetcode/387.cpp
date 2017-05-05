class Solution {
public:
    int firstUniqChar(string s) {
        int cnt[26] = {0};
        
        for (int i = 0; i < s.size(); i++) {
            cnt[s[i] - 'a']++;
        }
        
        for (int i = 0; i < s.size(); i++) {
            if (1 == cnt[s[i] - 'a'])
                return i;
        }
        return -1;
    }
};
