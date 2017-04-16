class Solution {
public:
    int findComplement(int num) {
        uint32_t mask = ~0;
        while (mask & num)
            mask <<= 1;
        return ~num & ~mask;
    }
};
