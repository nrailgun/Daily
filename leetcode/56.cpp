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
    static bool interval_less(const Interval &lhs, const Interval &rhs) {
        return lhs.start < rhs.start;
    }

    vector<Interval> merge(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), interval_less);
        
        vector<Interval> v;
        for (int i = 0; i < intervals.size(); i++) {
            Interval itv = intervals[i];
            
            for (int j = i + 1; j < intervals.size(); j++) {
                Interval itv2 = intervals[j];
                if (itv2.start <= itv.end) {
                    i++;
                    if (itv2.end > itv.end)
                        itv.end = itv2.end;
                } else {
                    break;
                }
            }
            v.push_back(itv);
        }
        
        return v;
    }
};
