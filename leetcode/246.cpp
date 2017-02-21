class Solution {
public:
    char rotate(char d) {
        char a[] = { '0', '1', 0, 0, 0, 0, '9', 0, '8', '6' };
        return a[d - '0'];
    }

    bool isStrobogrammatic(string num) {
        int n = num.size();
        for (int i = 0; i < (n+1) / 2; i++) {
            char d = rotate(num[i]);
            if (0 == d || num[n-1-i] != d)
                return false;
        }
        return true;
    }
};
