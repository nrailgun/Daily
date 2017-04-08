class Solution {
public:
    int lengthOfLastWord(const string &s) {
        int n = s.size();
        int i, j;
        
        j = n - 1;
        while (j >= 0 && s[j] == ' ') {
            j--;
        }
        
        if (j < 0)
            return 0;
            
        i = j;
        while (i >= 0 && s[i] != ' ') {
            i--;
        }
        return j - i;
    }
};
