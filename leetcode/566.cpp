class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        int m = nums.size();
        if (!m)
            return nums;
        int n = nums[0].size();
        if (!n || m * n != r * c)
            return nums;
        
        vector<vector<int>> output(r, vector<int>(c));
        for (int i = 0; i < m * n; i++) {
            output[i / c][i % c] = nums[i / n][i % n];
        }
        return output;
    }
};
