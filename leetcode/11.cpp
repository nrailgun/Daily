// 中间的高度与容量无关，脑子不清楚被绕进去了。只要把短的一侧内移就可能得到更大的解。
// 启发：如果思路想不通，就写几个实际 case 说不定思路就突然意识到了。
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
