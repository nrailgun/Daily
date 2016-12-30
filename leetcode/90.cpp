// 这个题目有两个点：1. DFS 产生子集；2. 对于算法做简单的修改，避免重复情况。
class Solution {
public:
    // 注意这个实现不同之处。之前是每个元素放入不放入作为一层，现在是迭代每个放入。
    // 两种不同的算法，决定了算法是不是容易修改。
    void subsets(vector<int> &nums, const int from, vector<int> &v, vector<vector<int>> &vs) {
        vs.push_back(v);
        for (int i = from; i < nums.size(); i++) {
            // 对于算法做简单的修改，避免重复情况。
            if (i > from && nums[i] == nums[i-1])
                continue;
            v.push_back(nums[i]);
            subsets(nums, i + 1, v, vs);
            v.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> v;
        vector<vector<int>> vs;
        subsets(nums, 0, v, vs);
        return vs;
    }
};
