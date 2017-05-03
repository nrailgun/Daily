class Solution {
public:
    int findNthDigit(int n) {
        long long l = 1, base = 9;
        long long cnt = 0;
        while (cnt + l * base < n) {
            cnt += l * base;
            l++;
            base *= 10;
        }
        
        long long ti = base / 9 + (n - cnt - 1) / l;
        string s = to_string(ti);
        return s[(n - cnt - 1) % l] - '0';
    }
};
