// Moore voting 算法的改版，嘻嘻，我真机智。
// 但是注意如果不存在 majority number 就会出错，所以最后还要 O(n) 时间检查一遍。
// 还有一点不太重要的就是其实 v[2] 和 c[2] 的空间都可以节约掉。
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int *a = nums.data();
        int  n = nums.size();
        if (n == 0)
            return vector<int>();
        
        int v[3], c[3] = {0, 0, 0};
        for (int i = 0; i < n; i++) {
            int ai = a[i];

            if (c[0] != 0 && ai == v[0]) {
                c[0]++;
            } else if (c[1] != 0 && ai == v[1]) {
                c[1]++;
            } else if (c[2] != 0 && ai == v[2]) {
                c[2]++;
            } else if (c[0] == 0) {
                v[0] = ai;
                c[0] = 1;
            } else if (c[1] == 0) {
                v[1] = ai;
                c[1] = 1;
            } else if (c[2] == 0) {
                v[2] = ai;
                c[2] = 1;
            } else {
                assert(false);
            }
            
            if (c[0] > 0 && c[1] > 0 && c[2] > 0) {
                c[0]--;
                c[1]--;
                c[2]--;
            }
        }
        
        vector<int> rv;
        for (int i = 0; i < 3; i++) {
            if (c[i] == 0)
                continue;
            int cnt = 0;
            for (int j = 0; j < n; j++)
                if (a[j] == v[i])
                    cnt++;
            if (cnt > n / 3)
                rv.push_back(v[i]);
        }
        return rv;
    }
};
