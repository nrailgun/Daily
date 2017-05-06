// math trick.

class Solution {
public:
    int minMoves(vector<int>& nums) {
        long minv = *min_element(nums.begin(), nums.end());
        long sumv = accumulate(nums.begin(), nums.end(), 0);
        
        return sumv - nums.size() * minv;
    }
};
