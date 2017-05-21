class Solution {
public:
    int findPoisonedDuration(vector<int>& times, int duration) {
        int cnt = 0;
        int end = 0;
        
        for (int i = 0; i < times.size(); i++) {
            int t = times[i];
            if (t < end) {
                cnt += t + duration - end;
            } else {
                cnt += duration;
            }
            end = t + duration;
        }
        return cnt;
    }
};
