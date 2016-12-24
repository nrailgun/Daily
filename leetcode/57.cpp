/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    bool overlap(const Interval &lhs, const Interval &rhs) {
        return (lhs.start >= rhs.start && lhs.start <= rhs.end) || (rhs.start >= lhs.start && rhs.start <= lhs.end);
    }

    vector<Interval> insert(vector<Interval>& intervals, Interval ni) {
        if (intervals.size() == 0) {
            vector<Interval> v2;
            v2.push_back(ni);
            return v2;
        }

        vector<Interval> v;
        bool in = false;
        for (int i = 0; i < intervals.size(); i++) {
            if (!in && ni.start <= intervals[i].start) {
                v.push_back(ni);
                in = true;
            }
            v.push_back(intervals[i]);
        }
        if (!in)
            v.push_back(ni);
        
        vector<Interval> v2;
        v2.push_back(v[0]);
        for (int i = 1; i < v.size(); i++) {
            if (overlap(v2.back(), v[i])) {
                v2.back().end = max(v2.back().end, v[i].end);
            } else {
                v2.push_back(v[i]);
            }
        }
        return v2;
    }
};
