class Solution {
public:
    int maxArea(vector<int>& heights) {
        int n = heights.size();
        int i = 0, j = n - 1;
        
        int maxw = 0;
        while (i < j) {
            maxw = max(maxw, (j - i) * min(heights[i], heights[j]));
            
            if (heights[i] < heights[j])
                i++;
            else
                j--;
        }
        return maxw;
    }
};
