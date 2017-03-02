// Naive solution.
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int it = 0;
        for (int i = 0; i < s.size(); i++) {
            int j;
            for (j = it; j < t.size(); j++) {
                if (t[j] == s[i]) {
                    it = j + 1;
                    break;
                }
            }
            if (j == t.size())
                return false;
        }
        return true;
    }
};
