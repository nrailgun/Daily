class LongestDistance {
public:
  int getDis(const vector<int> &A, int n) {
    if (n == 0)
      return 0;

    int maxd = 0;
    int minv = A[0];
    for (int i = 1; i < n; i++) {
      int d = A[i] - minv;
      if (d > maxd) {
        maxd = d;
      }
      minv = min(minv, A[i]);
    }
    return maxd;
  }
};
