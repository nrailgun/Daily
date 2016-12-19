// 我的思路，O(n) 时间复杂度，代码略蠢。基于偶数个负数 product 为正数的性质。
class Solution {
public:
    int solve(const int ns[], const int from, const int to, int prods[]) {
        int ncnt = 0;
        int lidx = -1, ridx = -1, prod = 1;
        
        if (from == to)
            return 0;
        else if (from + 1 == to)
            return ns[from];
        
        for (int i = from; i < to; i++) {
            if (ns[i] < 0) {
                ridx = i;
                if (lidx == -1)
                    lidx = i;
                ncnt++;
            }
            prod *= ns[i];
            prods[i] = prod;
        }
        
        if (ncnt % 2 == 0) {
            return prod;
        } else {
            int v1 = lidx == from ? INT_MIN : prods[lidx - 1];
            int v2 = lidx == to-1 ? INT_MIN : prod / prods[lidx];
            int v3 = ridx == from ? INT_MIN : prods[ridx - 1];
            int v4 = ridx == to-1 ? INT_MIN : prod / prods[ridx];
            return max(max(v1, v2), max(v3, v4));
        }
    }

    int maxProduct(vector<int>& nums) {
        int mp = INT_MIN;
        int *ns = nums.data();
        int n = nums.size();
        vector<int> prods(n);
        bool zero = false;
        for (int i = 0, j = 0; i <= n; i++) {
            if (i < n && ns[i] == 0)
                zero = true;
            if (i == n || ns[i] == 0) {
                int p = solve(ns, j, i, prods.data());
                mp = max(mp, p);
                j = i + 1;
            }
        }
        return zero ? max(mp, 0) : mp;
    }
};

// 动态规划可能是更好的解法。
// TODO: 学习动态规划。
