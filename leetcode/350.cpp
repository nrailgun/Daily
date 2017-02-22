class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m;
        for (int i = 0; i < nums1.size(); i++) {
            m[nums1[i]]++;
        }
        
        vector<int> v;
        for (int i = 0; i < nums2.size(); i++) {
            int &c = m[nums2[i]];
            if (c > 0) {
                c--;
                v.push_back(nums2[i]);
            }
        }
        return v;
    }
};
