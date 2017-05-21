// You might use binary search. But solving quadratic equation is a better idea.
// Also, notice that 8*n might exceed INT_MAX.

class Solution {
public:
    int arrangeCoins(int n) {
        int k = (-1 + sqrt(1 + 8l * n)) / 2;
        return k;
    }
};
