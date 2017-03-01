// DP。一般算法是最好了，但是存在数学解法。
class Solution {
public:
    int integerBreak(int n) {
        static vector<int> ibs(2, 1);
        
        for (int i = ibs.size(); i <= n; i++) {
            int maxp = 0;
            for (int j = 1; j <= i / 2; j++) {
                int i1 = max(j, ibs[j]);
                int i2 = max(i - j, ibs[i - j]);
                maxp = max(maxp, i1 * i2);
            }
            ibs.push_back(maxp);
        }
        return ibs[n];
    }
};

// O(1) 时间可解出。
// O(7) = 3 * 2 * 2, O(8) = 3 * 3 * 2, O(9) = 3 * 3 * 3, O(10) = 3 * 3 * 2 * 2.
class Solution {
public:
    int integerBreak(int n) {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;
        
        int n2 = 0;
        if (n % 3)
            n2 = 3 - n % 3;

        int n3 = n / 3;
        if (n % 3 == 1) {
            n3 = (n - 4) / 3;
        }
        
        return pow(3, n3) * pow(2, n2);
    }
};
