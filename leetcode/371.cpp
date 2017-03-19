class Solution {
public:
    int getSum(int a, int b) {
        if (!b)
            return a;

        int s = a ^ b;
        int c = (a & b) << 1;
        return getSum(s, c);
    }
};
