class Comparator {
public:
    bool operator()(const Interval &lhs, const Interval &rhs) const {
        return lhs.end < rhs.end;
    }
};

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        Comparator comp;
        sort(intervals.begin(), intervals.end(), comp);
        
        int last = -1, cnt = 0;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i].start < last)
                return false;
            last = intervals[i].end;
        }
        return true;
    }
};
