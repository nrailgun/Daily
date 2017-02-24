// 寻找第 k 大数，利用快排分割，分而治之，在 O(n) 时间找到。
// 寻找第 k 多数，利用 heap。

// 注意 c++ PriorityQueue 的模板的格式。
class Comparator {
public:
	unordered_map<int, int> *i2c;
	Comparator(unordered_map<int, int> *m)
		: i2c(m) {
	}

	bool operator()(int i, int j) const {
		return (*i2c)[i] > (*i2c)[j];
	}
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> i2c;
        for (int i : nums) {
            i2c[i]++;
        }
        
        Comparator comp(&i2c);
        priority_queue<int, vector<int>, Comparator> pq(comp);
        
        for (auto it = i2c.begin(); it != i2c.end(); it++) {
            pq.push(it->first);
            if (pq.size() == k + 1) {
                pq.pop();
            }
        }
        
        vector<int> rv;
        while (!pq.empty()) {
            int i = pq.top();
            pq.pop();
            rv.push_back(i);
        }
        return rv;
    }
};

// 利用 Pair 的 relational operators 可以大大减少编程量。
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> i2c;
        for (int i : nums) {
            i2c[i]++;
        }
        
        priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
        
        for (auto it = i2c.begin(); it != i2c.end(); it++) {
            pair<int, int> p(it->second, it->first); // freq -> val
            pq.push(p);
            if (pq.size() == k + 1) {
                pq.pop();
            }
        }
        
        vector<int> rv;
        while (!pq.empty()) {
            pair<int, int> p = pq.top();
            pq.pop();
            rv.push_back(p.second);
        }
        return rv;
    }
};

// 务必注意细节优化和算法优化，push 次数不变，但是可以减少 Pop 次数（通常 k << unique element number）。
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> i2c;
        for (int i : nums) {
            i2c[i]++;
        }
        
        priority_queue< pair<int, int>, vector<pair<int, int>> > pq;
        vector<int> rv;
        for (auto it = i2c.begin(); it != i2c.end(); it++) {
            pair<int, int> p(it->second, it->first); // freq -> val
            pq.push(p);
            // 好过 pq.size() == i2c.size() - k + 1
            if (pq.size() > i2c.size() - k) {
                rv.push_back(pq.top().second);
                pq.pop();
            }
        }
        return rv;
    }
};
