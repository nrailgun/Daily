// Presum + HashMap. Haha.
class Solution {
public:
    int findMaxLength(vector<int>& ns) {
        int n = ns.size();
        
        unordered_map<int, int> s2i;
        s2i[0] = 0;
        int score = 0, maxl = 0;
        for (int i = 0; i < n; i++) {
            if (ns[i] == 1)
                score++;
            else
                score--;
            
            auto it = s2i.find(score);
            if (it == s2i.end()) {
                s2i[score] = i + 1;
            } else {
                int idx = it->second;
                maxl = max(maxl, i + 1 - idx);
            }
        }
        return maxl;
    }
};
