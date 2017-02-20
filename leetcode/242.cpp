class Solution {
public:
    bool isAnagram(string s, string t) {
        int cnt1[256] = { 0 }, cnt2[256] = { 0 };
        
        if (s.size() != t.size())
            return false;
        
        for (int i = 0; i < s.size(); i++) {
            cnt1[s[i]]++;
            cnt2[t[i]]++;
        }
        
        for (int i = 'a'; i <= 'z'; i++) {
            if (cnt1[i] != cnt2[i])
                return false;
        }
        return true;
    }
};
