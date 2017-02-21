// 注意 hIndex 的取值空间。
// 这是一个值得思考的问题，是一个比较广泛的思路，如果取值空间较小，可以利用内存实现高效的算法。
class Solution {
public:
    int hIndex(vector<int>& cs) {
        int n = cs.size();
        vector<int> his(n + 1, 0);

        for (vector<int>::iterator it = cs.begin(); it != cs.end(); it++)
            his[min(*it, n)]++;
        
        int s = 0;
        for (int i = n; i >= 0; i--) {
            s += his[i];
            if (s >= i)
                return i;
        }
        return 0;
    }
};
