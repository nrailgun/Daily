// Merge sort 变种，然后稍微加一点编程技巧。

class Entry {
public:
  int idx, e, cnt;

  Entry() : idx(0), e(0), cnt(0) {
  }

  bool operator<(const Entry &rhs) const {
    return idx < rhs.idx;
  }
};

class Solution {
public:
  vector<int> countSmaller(const vector<int> &nums) {
    int n = nums.size();
    vector<int> rv(n);
    vector<Entry> ents(n);
    vector<Entry> holder(n);

    if (n == 0)
      return rv;

    for (int i = 0; i < n; i++) {
      ents[i].idx = i;
      ents[i].e = nums[i];
    }
    merge_count(ents, 0, n - 1, holder);
    sort(ents.begin(), ents.end());
    for (int i = 0; i < n; i++) {
      rv[i] = ents[i].cnt;
    }
    return rv;
  }

  void merge_count(vector<Entry> &ents, int lb, int ub, vector<Entry> &holder) {
    if (ub <= lb)
      return;

    int mid;
    int i, j, k, incre;

    mid = (lb + ub) / 2;
    merge_count(ents, lb, mid, holder);
    merge_count(ents, mid + 1, ub, holder);

    i = lb;
    j = mid + 1;
    k = lb;
    incre = 0;
    while (i <= mid && j <= ub) {
      if (ents[i].e <= ents[j].e) {
        holder[k] = ents[i];
        holder[k].cnt += incre;
        //printf("< holder[%d].cnt = %d, incre + %d\n", k, holder[k].cnt, incre);
        i++;
        k++;
      }
      else { // if (ents[i].e > ents[j].e) {
        holder[k] = ents[j];
        incre++;
        //printf("> holder[%d].cnt = %d, incre + %d\n", k, holder[k].cnt, incre);
        j++;
        k++;
      }
    }
    while (i <= mid) {
      holder[k] = ents[i];
      holder[k].cnt += incre;
      i++;
      k++;
    }
    while (j <= ub) {
      holder[k] = ents[j];
      j++;
      k++;
    }
    copy(holder.begin() + lb, holder.begin() + ub + 1, ents.begin() + lb);
  }
};
