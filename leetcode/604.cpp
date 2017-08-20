class StringIterator {
public:
  string s;
  int n;
  int ci;
  char c;
  int cnt;

  StringIterator(const string &cs) : n(cs.size()), ci(0), c(0), cnt(0) {
    s = cs;
  }

  char next() {
    if (!hasNext())
      return ' ';

    if (cnt > 0) {
      cnt--;
    }
    else {
      c = s[ci];
      ci++;
      while (isdigit(s[ci])) {
        cnt *= 10;
        cnt += s[ci] - '0';
        ci++;
      }
      cnt--;
    }
    return c;
  }

  bool hasNext() const {
    return cnt > 0 || ci < n;
  }
};
