class Solution {
public:
    int reverse(int x) {
        long long int rv = 0;
        while (x) {
            rv *= 10;
            rv += x % 10;
            x /= 10;
        }
        return (rv < INT_MIN || rv > INT_MAX) ? 0 : rv;
    }
};
