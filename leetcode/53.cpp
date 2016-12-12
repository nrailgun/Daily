// 我的思路。和数组可以很快求段内和。最大段和就是当前 sum - 之前最小 sum。
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int mins = 0, s = 0, rv = -INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            s += nums[i];
            rv = max(rv, s - mins);
            mins = min(mins, s);
        }
        return rv;
    }
};

// 另一个思路。sum < 0 的段无帮助，跳过。
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int s = 0, maxs = -INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            if (s < 0)
                s = 0;
            s += nums[i];
            if (s > maxs)
                maxs = s;
        }
        return maxs;
    }
};
