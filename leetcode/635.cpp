class LogSystem {
public:

  class Timestamp {
  public:
    string s_;
    int year_, month_, day_, hour_, minute_, second_;
    long long int val_;

    Timestamp(const string &s) : s_(s) {
      sscanf(s.c_str(), "%d:%d:%d:%d:%d:%d", &year_, &month_, &day_, &hour_, &minute_, &second_);
      year_ -= 2000;
      month_--;
      day_--;
      val_ = makeVal();
    }

    long long int makeVal() const {
      long long int val = 0;

      val = year_;
      val = val * 12 + month_;
      val = val * 31 + day_;
      val = val * 24 + hour_;
      val = val * 60 + minute_;
      val = val * 60 + second_;
      return val;
    }

    bool operator<(const Timestamp &rhs) const {
      return val_ < rhs.val_;
    }

    int granulartyToInt(const string &gras) const {
      if (gras == "Year")
        return 0;
      if (gras == "Month")
        return 1;
      if (gras == "Day")
        return 2;
      if (gras == "Hour")
        return 3;
      if (gras == "Minute")
        return 4;
      if (gras == "Second")
        return 5;
      assert(0);
      return -1;
    }

    void alterToRange(const string &_gra, bool isBeg) {
      int gra = granulartyToInt(_gra);
      switch (gra) {
      case 0: // Year
        month_  = isBeg ? 0 : 11;
      case 1: // Month
        day_    = isBeg ? 0 : 30;
      case 2: // Day
        hour_   = isBeg ? 0 : 23;
      case 3: // Hour
        minute_ = isBeg ? 0 : 59;
      case 4: // Minute
        second_ = isBeg ? 0 : 59;
      }
      val_ = makeVal();
    }

    string toString() const {
      char buf[1024];
      snprintf(buf, sizeof(buf), "%d:%d:%d:%d:%d:%d", year_, month_, day_, hour_, minute_, second_);
      return buf;
    }
  };

  map<Timestamp, int> timestamps;

  LogSystem() {
  }

  void put(int id, const string &timestamp) {
    Timestamp ts(timestamp);
    timestamps[ts] = id;
  }

  vector<int> retrieve(const string &s, const string &e, const string &gra) {
    vector<int> vi;

    Timestamp tss(s);
    tss.alterToRange(gra, true);
    Timestamp tse(e);
    tse.alterToRange(gra, false);

    auto sit = timestamps.lower_bound(tss);
    auto eit = timestamps.upper_bound(tse);
    for (auto it = sit; it != eit; it++) {
      vi.push_back(it->second);
    }
    return vi;
  }
};
