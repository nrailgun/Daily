// 双指针法，无特别。注意逻辑问题，当 `from == nums.size() - 2` 的时候，`lb < ub` 会直接跳过，返回 INT_MAX。
// 后面 INT_MAX 参与计算，比如 + 1，导致计算溢出，所以对于返回值可能是 INT_MAX 这些极端值的数字，小心参与计算。
// 同时，广泛的，循环体要注意进入循环/不进入循环两种情况下的逻辑。
class Solution {
public:
    int solve(const vector<int> &nums, const int from, const int target) {
        int lb = from + 1, ub = nums.size() - 1;
        int s = INT_MAX;
        bool init = false;
        while (lb < ub) {
            int sum3 = nums[from] + nums[lb] + nums[ub];
            if (!init) {
                s = sum3;
                init = true;
            }
            else if (abs(sum3 - target) < abs(s - target)) {
                s = sum3;
            }
            
            if (sum3 > target) {
                ub--;
            } else if (sum3 < target) {
                lb++;
            } else {
                return sum3;
            }
        }
        return s;
    } 

    int threeSumClosest(vector<int>& nums, const int target) {
        sort(nums.begin(), nums.end());
        int closest = INT_MAX;
        bool init = false;
        for (int i = 0; i < nums.size(); i++) {
            int t = solve(nums, i, target);
            if (!init) {
                closest = t;
                init = true;
            }
            else if (abs(t - target) < abs(closest - target)) {
                closest = t;
            }
        }
        return closest;
    }
};
// 比较合理的实现。
class Solution {
public:
    int threeSumClosest(vector<int>& nums, const int target) {
        sort(nums.begin(), nums.end());
        int closest = INT_MAX;
        bool init = false;
        for (int from = 0; from < nums.size(); from++) {
            int lb = from + 1, ub = nums.size() - 1;
            while (lb < ub) {
                int sum3 = nums[from] + nums[lb] + nums[ub];
                if (!init || abs(sum3 - target) < abs(closest - target)) {
                    closest = sum3;
                    init = true;
                }
                if (sum3 < target) {
                    lb++;
                } else if (sum3 > target) {
                    ub--;
                } else {
                    return sum3;
                }
            }
        }
        return closest;
    }
};
