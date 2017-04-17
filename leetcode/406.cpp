// 一般来说没有 random access 且 O(1) Insert/Erase 的数据结构。

bool compare(pair<int, int> &p1, pair<int, int> &p2) {
    if (p1.first != p2.first)
        return p1.first > p2.first;
    else
        return p1.second < p2.second;
}

class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), compare);
        
        vector<pair<int, int>> res;
        for (int i = 0; i < people.size(); i++) {
            res.insert(res.begin() + people[i].second, people[i]);
        }
        return res;
    }
};
