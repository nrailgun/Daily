class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        int rv = 0;
        
        if (nums.size() == 0 || k < 0)
            return 0;
        else if (k == 0) {
            sort(nums.begin(), nums.end());
            
            for (int i = 0; i < nums.size() - 1; ) {
                if (nums[i] != nums[i + 1])
                    i++;
                else {
                    i++;
                    while (i < nums.size() && nums[i] == nums[i-1])
                        i++;
                    rv++;
                }
            }
        }
        else {
            unordered_set<int> s(nums.begin(), nums.end());
            for (auto i : s) {
                int t = i + k;
                if (s.find(t) != s.end()) {
                    rv++;
                }
            }
        }
        return rv;
    }
};
