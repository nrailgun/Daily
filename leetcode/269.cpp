// Topological sort.

class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<int> inds(256, 0);
        vector<vector<int>> deps(256, vector<int>());
        unordered_set<char> charset;
        
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                charset.insert(words[i][j]);
            }
        }
        
        for (int i = 0; i < words.size() - 1; i++) {
            for (int j = 0; j < min(words[i].size(), words[i+1].size()); j++) {
                if (words[i][j] != words[i+1][j]) {
                    deps[words[i][j]].push_back( words[i+1][j] );
                    inds[words[i+1][j]]++;
                    break; // 注意此处，应该 break，后面的单词没有比较的意义，否则出错。
                }
            }
        }
        
        vector<int> zins;
        for (auto i : charset) {
            if (!inds[i])
                zins.push_back(i);
        }
        
        int k = 0;
        while (k < zins.size()) {
            int i = zins[k++];
            for (int j : deps[i]) {
                if (--inds[j] == 0) {
                    zins.push_back(j);
                }
            }
        }
        
        if (zins.size() != charset.size())
            return "";
        else
            return string(zins.begin(), zins.end());
    }
};
