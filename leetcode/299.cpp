class Solution {
public:
    string getHint(string s, string g) {
        int b[256] = { 0 };
    
        int A = 0;
        for (int i = 0; i < s.size(); i++) {
            if (g[i] == s[i])
                A++;
            else
                b[s[i]]++;
        }
        
        int B = 0;
        for (int i = 0; i < s.size(); i++) {
            if (g[i] != s[i] && b[g[i]] > 0) {
                b[g[i]]--;
                B++;
            }
        }
        
        string rv = to_string(A) + 'A' + to_string(B) + 'B';
        return rv;
    }
};
