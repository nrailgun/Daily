//TODO: learn STL implementation.
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int>::iterator lb = lower_bound(nums.begin(), nums.end(), target);
        vector<int>::iterator ub = upper_bound(nums.begin(), nums.end(), target);
        
        vector<int> rv(2, -1);
        if (*lb == target) {
            
            rv[0]=(distance(nums.begin(), lb));
            rv[1]=(distance(nums.begin(), ub)-1);
        }
        return rv;
    }
};
