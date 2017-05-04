class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num <= 1)
            return false;

        int s = 1;
        for (int i = 2; i <= sqrt(num); i++) {
            if (0 == num % i) {
                s += num / i;
                s += i;
            }
        }
        return s == num;
    }
};
