//没必要建立索引，因为只会查询一次。其次，最小距离只能是在相邻的两个位置，所以只要记录 word1 和 word2 最近出现的位置就好。
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int p1 = -1, p2 = -1;
        int mind = INT_MAX;
        
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
        return mind;
    }
};
