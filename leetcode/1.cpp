class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> v(2, -1);
        map<int, int> m;
        
        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            map<int, int>::iterator it = m.find(diff);
            if (it == m.end()) {
                m.insert(make_pair(nums[i], i));
            } else {
                v[0] = it->second;
                v[1] = i;
            }
        }
        return v;
    }
};
