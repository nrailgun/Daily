class Solution {
public:
    bool canPermutePalindrome(string s) {
        int cnt[256] = { 0 };
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            cnt[ch] = 1 - cnt[ch];
        }
        
        int c = count(cnt, cnt + 256, 1);
        return c <= 1; // s.size() % 2 ? c == 1 : c == 0;
    }
};

// Using bitset.
class Solution {
public:
    bool canPermutePalindrome(string s) {
        bitset<256> b;
        for (int i = 0; i < s.size(); i++) {
            b.flip(s[i]);
        }
        return b.count() <= 1;
    }
};
