class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
            
        int x1 = x;
        int y = 0;
        while (x1) {
            y *= 10;
            y += x1 % 10;
            x1 /= 10;
        }
        return y == x;
    }
};
