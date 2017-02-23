// Regular approach, using counters.
class Solution {
public:
    char findTheDifference(string s, string t) {
        int cnts[256] = { 0 };
        int n = s.size();
        
        for (int i = 0; i < n; i++) {
            cnts[s[i]]++;
            cnts[t[i]]--;
        }
        cnts[t[n]]--;
        
        for (int i = 'a'; i <= 'z'; i++)
            if (cnts[i] < 0)
                return i;
        return 0;
    }
};

// 技巧：XOR 可以用来消除数列中成对的数。虽然并没有快多少。
class Solution {
public:
    char findTheDifference(string s, string t) {
        int rv = 0;
        int n = s.size();
        
        for (int i = 0; i < n; i++) {
            rv ^= s[i];
            rv ^= t[i];
        }
        rv ^= t[n];
        
        return rv;
    }
};
