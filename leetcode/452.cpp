bool compare(const pair<int, int> &p1, const pair<int, int> &p2) {
    if (p1.second != p2.second)
        return p1.second < p2.second;
    else
        return p1.first < p2.first;
}

class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if (points.size() == 0)
            return 0;

        sort(points.begin(), points.end(), compare);
        int cnt = 1;
        int last = 0;
        for (int i = 1; i < points.size(); i++) {
            if (points[i].first > points[last].second) {
                last = i;
                cnt++;
            }
        }
        return cnt;
    }
};
