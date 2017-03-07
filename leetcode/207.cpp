// By topological sort.

class Solution {
public:
    bool canFinish(int n, vector<pair<int, int>>& pres) {
        vector<int> inds(n, 0);
        vector<vector<int>> prem(n, vector<int>());
        
        for (auto pr : pres) {
            inds[pr.second]++;
            prem[pr.first].push_back(pr.second);
        }
        
        queue<int> zins;
        for (int i = 0; i < n; i++) {
            if (inds[i] == 0)
                zins.push(i);
        }
        
        int ok = 0;
        while (!zins.empty()) {
            int zin = zins.front();
            zins.pop();
            ok++;
            
            for (int j : prem[zin]) {
                if (0 == --inds[j]) {
                    zins.push(j);
                }
            }
        }
        return ok == n;
    }
};
