class Solution {
public:
    typedef pair<int, int> Point;

    bool isReflected(vector<Point>& pts) {
        unordered_map<int, unordered_set<int>> x2ys;
        
        int minx = INT_MAX, maxx = INT_MIN;
        for (int i = 0; i < pts.size(); i++) {
            minx = min(minx, pts[i].first);
            maxx = max(maxx, pts[i].first);
            x2ys[ pts[i].first ].insert(pts[i].second);
        }
        
        int refsum = maxx + minx;
        for (int i = 0; i < pts.size(); i++) {
            int x1 = pts[i].first, y1 = pts[i].second;
            int x2 = refsum - x1;
            unordered_map<int, unordered_set<int>>::const_iterator it = x2ys.find(x2);
            if (it == x2ys.end())
                return false;
            if (it->second.find(y1) == it->second.end())
                return false;
        }
        return true;
    }
};
