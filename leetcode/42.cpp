class Solution {
public:
    int trap(vector<int>& heights) {
        vector<int> fhs, bhs;
        
        int h, fprevh = 0, bprevh = 0;
        for (int i = 0; i < heights.size(); i++) {
            h = heights[i];
            fprevh = max(fprevh, h);
            fhs.push_back(fprevh);
            
            h = heights[heights.size() - 1 - i];
            bprevh = max(bprevh, h);
            bhs.push_back(bprevh);
        }
        reverse(bhs.begin(), bhs.end());
        
        int rv = 0;
        for (int i = 0; i < heights.size(); i++) {
            int d = min(fhs[i], bhs[i]);
            rv += d - heights[i];
        }
        return rv;
    }
};
