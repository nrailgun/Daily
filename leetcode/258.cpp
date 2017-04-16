class Solution {
public:

    // (100a+10b+c)%9=(a+99a+b+9b+c)%9=(a+b+c)%9
    int addDigits(int num) {
        if (num == 0)
            return 0;
        else
            return num % 9 ? num % 9 : 9;
    }
};
