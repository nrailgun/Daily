// 对于内存关键的场合，map 和 set 如果导致内存不足，又需要快速检索，一般依赖 sort 和 bsearch。
class Solution {
public:
    multimap<int, int> iis;

    Solution(vector<int> nums) {
        for (int i = 0; i < nums.size(); i++) {
            iis.insert(make_pair(nums[i], i));
        }
    }
    
    int pick(int target) {
        auto it = iis.lower_bound(target);

        int i = 2, idx = it->second;
        it++;
        while (it != iis.end() && it->first == target) {
            if (rand() % i++ == 0) {
                idx = it->second;
            }
            it++;
        }
        return idx;
    }
};

// 正确解法。注意，这个地方使用储水池算法纯属画蛇添足，因为 list 是 random access 的。
// 无力吐槽的是这题目 O(n) 的查找算法居然比 O(logn) 要快，这数据不科学。
class Comparator {
public:
    bool operator()(const pair<int, int> &i, const pair<int, int> &j) const {
        return i.first < j.first;
    }
};

class Solution {
public:
    vector<pair<int, int>> v;
    Comparator comp;

    Solution(const vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            v.push_back(make_pair(nums[i], i));
        }
        sort(v.begin(), v.end(), comp);
    }
    
    int pick(int target) {
        auto bound = equal_range(v.begin(), v.end(), make_pair(target, 0), comp);
        int lb = bound.first - v.begin(), ub = bound.second - v.begin();
        int idx = lb + rand() % (ub - lb);
        return v[idx].second;
    }
};

