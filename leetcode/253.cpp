class Time {
public:
  int time;
  bool end;
  
  Time(int t, bool e) : time(t), end(e) {}
};

bool comp(const Time &t1, const Time &t2) {
  if (t1.time == t2.time)
    return t1.end && !t2.end;
  return t1.time < t2.time;
}

class Solution {
public:
  int minMeetingRooms(vector<Interval>& intervals) {
    vector<Time> tv(intervals.size() * 2, Time(0, false));
    for (int i = 0; i < intervals.size(); i++) {
      tv[2*i] = Time(intervals[i].start, false);
      tv[2*i+1] = Time(intervals[i].end, true);
    }
    sort(tv.begin(), tv.end(), comp);

    int cnt = 0, maxcnt = 0;
    for (int i = 0; i < tv.size(); i++) {
      if (tv[i].end)
        cnt--;
      else 
        cnt++;
      maxcnt = max(maxcnt, cnt);
    }
    return maxcnt;
  }
};
