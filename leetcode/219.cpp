// 排序索引，我真是太机智了。

class Comparator {
public:
    vector<int> *nums;

    Comparator(vector<int> &nums)
    : nums(&nums) {
    }

    bool operator()(int idx1, int idx2) const {
        return (*nums)[idx1] < (*nums)[idx2];
    }
};

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> idxs(n);
        for (int i = 0; i < n; i++)
            idxs[i] = i;
        sort(idxs.begin(), idxs.end(), Comparator(nums));
        
        for (int i = 0; i < n - 1; i++) {
            int idx1 = idxs[i];
            int idx2 = idxs[i+1];
            if (nums[idx1] == nums[idx2] && abs(idx1 - idx2) <= k)
                return true;
        }
        return false;
    }
};
