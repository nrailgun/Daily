// 非常 naive 的剪枝思路，低效。
class Solution {
public:
    int findCelebrity(int n) {
        vector<int> v(n);
        for (int i = 0; i < n; i++)
            v[i] = i;
        set<int> s(v.begin(), v.end());
        
        for (set<int>::const_iterator it1 = s.begin(); it1 != s.end(); it1++) {
            int v1 = *it1;
            for (set<int>::iterator it2 = s.begin(); it2 != s.end(); ) {
                int v2 = *it2;
                if (v1 != v2 && !knows(v1, v2)) {
                    it2 = s.erase(it2);
                } else {
                    it2++;
                }
            }
        }
        
        for (set<int>::const_iterator it1 = s.begin(); it1 != s.end(); it1++) {
            int v1 = *it1, j;
            for (j = 0; j < n; j++) {
                int v2 = v[j];
                if (v1 == v2)
                    continue;
                if (!knows(v2, v1) || knows(v1, v2))
                    break;
            }
            if (j == n)
                return v1;
        }
        return -1;
    }
};
