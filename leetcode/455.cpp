// Sort + Greedy.

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int cnt = 0;
        int i, j = 0;
        for (i = 0; i < s.size(); i++) {
            int cookie = s[i];
            if (cookie >= g[j]) {
                if (++j >= g.size())
                    break;
            }
        }
        return j;
    }
};
