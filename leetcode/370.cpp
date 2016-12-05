// 直接逐个元素求和超时。由于范围内的增量都是一样的，所以可以利用之前的计算结果。
// 记录下某个位置开始的增量，并在结束处减掉。用数组记录增减量，保持记录 sum。

class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> rv(length, 0);
        
        for (int u = 0; u < updates.size(); u++) {
            const vector<int> &update = updates[u];
            
            int startidx = update[0];
            int endidx = update[1];
            int inc = update[2];
            
            rv[startidx] += inc;
            if (endidx + 1 < length) {
                rv[endidx + 1] -= inc;
            }
        }
        
        for (int i = 0, sum = 0; i < length; i++) {
            sum += rv[i];
            rv[i] = sum;
        }
        return rv;
    }
};
