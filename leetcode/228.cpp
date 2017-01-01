class Solution {
public:
    string makes(int v1, int v2) {
        char buf[BUFSIZ];
        if (v1 == v2) {
            snprintf(buf, BUFSIZ, "%d", v1);
        } else {
            snprintf(buf, BUFSIZ, "%d->%d", v1, v2);
        }
        return string(buf);
    }

    vector<string> summaryRanges(vector<int>& nums) {
        int n = nums.size();
        vector<string> v;
        int from = 0;
        for (int i = 0; i < n; i++) {
            // 注意这里 nums[i+1]-nums[i]>1 会导致计算溢出，一点细节。
            if (i == n-1 || nums[i+1]>nums[i]+1) {
                v.push_back(makes(nums[from], nums[i]));
                from = i+1;
            }
        }
        return v;
    }
};
