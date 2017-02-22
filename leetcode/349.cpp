class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s(nums1.begin(), nums1.end());
        vector<int> rv;
        
        for (int i = 0; i < nums2.size(); i++) {
            int v = nums2[i];
            unordered_set<int>::iterator it = s.find(v);
            if (it != s.end()) {
                s.erase(it);
                rv.push_back(v);
            }
        }
        return rv;
    }
};
