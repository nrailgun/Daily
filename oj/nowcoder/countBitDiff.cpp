class Solution {
public:
  // what if < 0
  int countBitDiff(int m, int n) {
    int nbit = 8 * sizeof(int);
    int d = 0;

    for (int i = 0; i < nbit; i++) {
      if ((m & 1) ^ (n & 1))
        d++;
      m >>= 1;
      n >>= 1;
    }
    return d;
  }
};
