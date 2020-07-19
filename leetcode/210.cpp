class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& pres) {
        vector<vector<int>> deps(n);
        vector<int> inds(n, 0);
        for (auto pre : pres) {
            deps[pre[0]].push_back(pre[1]);
            inds[pre[1]]++;
        }
        
        vector<int> zins;
        for (int i = 0; i < n; i++) {
            if (inds[i] == 0)
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
        
        if (zins.size() < n) {
            return vector<int>();
        } else {
            reverse(zins.begin(), zins.end());
            return zins;
        }
    }
};
