class Solution {
public:
    bool detectCapitalUse(string &word) {
        int nu = 0;
        for (int i = 0; i < word.size(); i++)
            if (isupper(word[i]))
                nu++;
        
        return nu == 0 || nu == word.size() || (nu == 1 && isupper(word.front()));
    }
};
