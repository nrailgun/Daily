class Solution {
public:
    int bulbSwitch(int n) {
        int i = 0;
        int s = 0;
        while (s < n) {
            i++;
            s += 2 * i + 1;
        }
        return i;
    }
};
