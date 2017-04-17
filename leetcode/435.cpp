bool compare(const Interval &i1, const Interval &i2) {
    if (i1.end != i2.end)
        return i1.end < i2.end;
    else
        return i1.start > i2.start;
}

class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), compare);
        
        int n = intervals.size();
        int cnt = 0;
        int last = 0;
        for (int i = 1; i < n; i++) {
            if (intervals[i].start >= intervals[last].end) {
                last = i;
            } else {
                cnt++;
            }
        }
        return cnt;
    }
};
