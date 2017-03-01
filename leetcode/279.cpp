// 非常简单的 memorize 的暴力搜索。
class Solution {
public:
    int numSquares(int n) {
        vector<int> sols(n+1, 0);
        
        for (int i = 1; i <= n; i++) {
            int minc = INT_MAX;
            for (int j = 1; j * j <= i; j++) {
                minc = min(minc, 1 + sols[i - j * j]);
            }
            sols[i] = minc;
        }
        return sols[n];
    }
};

class Solution {
public:
    // 其实 DP 没有更加高级的算法了，仅仅是利用 static 成员避免重复计算，beat 86%。
    int numSquares(int n) {
        static vector<int> sols(1, 0);
        
        for (int i = sols.size(); i <= n; i++) {
            int minc = INT_MAX;
            for (int j = 1; j * j <= i; j++) {
                minc = min(minc, 1 + sols[i - j * j]);
            }
            sols.push_back(minc);
        }
        return sols[n];
    }
};
