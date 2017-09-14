class FirstRepeat {
public:
  char findFirstRepeat(const string &A, int n) {
    bitset<256> s;

    for (int i = 0; i < n; i++) {
      int c = A[i];
      if (s.test(c))
        return static_cast<char>(c);
      else {
        s.set(c, true);
      }
    }
    return 0;
  }
};
