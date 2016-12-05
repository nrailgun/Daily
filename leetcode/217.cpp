class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> s;
        for (vector<int>::const_iterator it = nums.begin(); it != nums.end(); it++) {
            if (s.find(*it) == s.end()) {
                s.insert(*it);
            } else {
                return true;
            }
        }
        return false;
    }
};
