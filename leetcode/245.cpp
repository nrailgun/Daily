class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int p1 = -1, p2 = -1;
        int mind = INT_MAX;
        
        if (word1 != word2) {
            for (int i = 0; i < words.size(); i++) {
                const string &word = words[i];
                if (word == word1) {
                    p1 = i;
                    if (p2 != -1) {
                        mind = min(p1 - p2, mind);
                    }
                } else if (word == word2) {
                    p2 = i;
                    if (p1 != -1) {
                        mind = min(p2 - p1, mind);
                    }
                }
            }
        } else {
            for (int i = 0; i < words.size(); i++) {
                const string &word = words[i];
                if (word == word1) {
                    p1 = p2;
                    p2 = i;
                    if (p1 != -1 && p2 != -1) {
                        mind = min(p2 - p1, mind);
                    }
                }
            }
        }
        return mind;
    }
};
