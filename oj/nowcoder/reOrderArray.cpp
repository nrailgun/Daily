class Solution {
public:
  void reOrderArray(vector<int> &a) {
    int n = a.size();

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - 1 - i; j++) {
        if (a[j] % 2 == 0 && a[j+1] % 2)
          swap(a[j], a[j+1]);
      }
    }
  }
};
