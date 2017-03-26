class HitCounter {
public:
  map<int, int> counter; // time -> count
  int s;
  
  HitCounter() : s(0) {
  }

  void expire(int t) {
    map<int, int>::iterator ub = counter.upper_bound(t - 300);
    for (map<int, int>::iterator it = counter.begin(); it != ub; it++) {
      s -= it->second;
    }
    counter.erase(counter.begin(), ub);
  }

  void hit(int t) {
    expire(t);
    counter[t]++;
    s++;
  }

  int getHits(int t) {
    expire(t);
    return s;
  }
};

