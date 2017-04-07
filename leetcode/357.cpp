// WTF.

class Solution {
public:
    int count(int n) {
        switch (n) {
        case 1:
            return 10;
        
        default:
            int p = 9;
            int i = 2;
            while (i <= n) {
                p *= 11 - i++;
            }
            return p;
        }
    }
    
    int countNumbersWithUniqueDigits(int n) {
        if (!n)
            return 1;
        int s = 0;
        for (int i = 1; i <= n; i++)
            s += count(i);
        return s;
    }
};
