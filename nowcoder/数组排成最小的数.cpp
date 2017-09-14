class Solution {
public:
  string PrintMinNumber(const vector<int> &nums) {
    vector<string> sv(nums.size());
    for (int i = 0; i < nums.size(); i++)
      sv[i] = to_string(nums[i]);
    sort(sv.begin(), sv.end(),
      [](const string &l, const string &rhs) { return (l + rhs) < (rhs + l); });
    return accumulate(sv.begin(), sv.end(), string(""));
  }
};
