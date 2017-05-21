// Forward declaration of guess API.
// @param num, your guess
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int lb = 1, ub = n;
        
        while (lb <= ub) {
            int mid = lb + (ub - lb) / 2;
            int g = guess(mid);
            if (g == 0) {
                return mid;
            } else if (g > 0) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        return INT_MAX;
    }
};
