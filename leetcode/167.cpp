class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i1, i2;
        vector<int> v;
        for (i1 = 0, i2 = numbers.size() - 1; i1 != i2; /**/) {
            int sum = numbers[i1] + numbers[i2];
            if (sum > target) {
                i2--;
            } else if (sum < target) {
                i1++;
            } else {
                v.push_back(i1 + 1);
                v.push_back(i2 + 1);
                break;
            }
        }
        return v;
    }
};
