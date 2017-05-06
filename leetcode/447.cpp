// 看起来很难，其实只有 O(n^2) 的无脑解法。

class Solution {
public:
    int distance(pair<int, int> &p1, pair<int, int> &p2) {
        int dx = p1.first - p2.first;
        int dy = p1.second - p2.second;
        return dx * dx + dy * dy;
    }

    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int n = points.size();
        int rv = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<int, int> cnt;
            pair<int, int> p1 = points[i];
            
            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                pair<int, int> p2 = points[j];
                int d = distance(p1, p2);
                cnt[d]++;
            }
            
            for (auto it = cnt.begin(); it != cnt.end(); it++) {
                rv += it->second * (it->second - 1);
            }
        }
        return rv;
    }
};
