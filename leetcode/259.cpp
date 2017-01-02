// 双指针法，机智。
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int *a = nums.data();
        
        int cnt = 0;
        for (int i = 0; i < n - 2; ) {
            int lb = i + 1, ub = n - 1;
            while (lb < ub) {
                int s = a[i] + a[lb] + a[ub];
                if (s >= target) {
                    ub--;
                } else {
                    cnt += ub - lb;
                    lb++;
                }
            }
            i++;
        }
        return cnt;
    }
};
