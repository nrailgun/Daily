// 经典找零问题。过了 100 年我终于解出来了，不过其实就是普通的 DP。
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> sol(amount + 1, 0);
        
        for (int i = 1; i <= amount; i++) {
            int minc = INT_MAX;
            for (int coin : coins) {
                if (coin <= i && sol[i - coin] != INT_MAX) {
                    minc = min(minc, 1 + sol[i - coin]);
                }
            }
            sol[i] = minc;
        }
        
        int rv = sol.back();
        return rv == INT_MAX ? -1 : rv;
    }
};
