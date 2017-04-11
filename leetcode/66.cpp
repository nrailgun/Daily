class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int i = digits.size() - 1;
        while (i >= 0 && ++digits[i] == 10) {
            digits[i] = 0;
            i--;
        }
        
        if (i < 0) {
            int n = digits.size();
            digits.resize(n + 1);
            copy_backward(digits.begin(), digits.begin() + n, digits.end());
            digits[0] = 1;
        }
        return digits;
    }
};
