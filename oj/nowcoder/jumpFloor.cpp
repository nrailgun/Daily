class Solution {
public:
    static vector<int> v;
    
    int jumpFloor(int n) {
        if (n >= v.size()) {
            v.push_back(jumpFloor(n - 1) + jumpFloor(n - 2));
        }
        return v[n];
    }
};

vector<int> Solution::v = { 0, 1, 2 };
