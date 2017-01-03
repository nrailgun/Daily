// 考虑到只有 k=3 的特殊情况，所以不需要通用 k-th max 算法。
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        vector<int> maxs;
        
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            bool dup = false;
            for (int j = 0; j < maxs.size(); j++) {
                if (nums[i] == maxs[j])
                    dup = true;
            }
            if (dup)
                continue;
            
            if (maxs.size() < 3) {
                maxs.push_back(nums[i]);
                sort(maxs.begin(), maxs.end());
            } else {
                if (nums[i] > maxs[0]) {
                    maxs[0] = nums[i];
                    sort(maxs.begin(), maxs.end());
                }
            }
        }
        return maxs.size() == 3 ? maxs.front() : maxs.back();
    }
};
// 实际用 set 并不会更快。
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> maxs;
        
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            maxs.insert(nums[i]);
            if (maxs.size() > 3) {
                maxs.erase(maxs.begin());
            }
        }
        return maxs.size() == 3 ? *maxs.begin() : *maxs.rbegin();
    }
};
