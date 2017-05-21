class RandomizedCollection {
public:
    vector<pair<int, int>> nums;
    unordered_map<int, vector<int>> n2is;

    /** Initialize your data structure here. */
    RandomizedCollection() {
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        auto it = n2is.find(val);
        bool rv = it == n2is.end();
        
        n2is[val].push_back(nums.size());
        nums.push_back( make_pair(val, n2is[val].size() - 1) );
        return rv;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        auto it = n2is.find(val);
        if (it == n2is.end())
            return false;
        
        int i = it->second.back();
        it->second.pop_back();
        if (it->second.empty()) {
            n2is.erase(it);
        }
        
        if (i == nums.size() - 1) {
            nums.pop_back();
        }
        else {
            pair<int, int> bkn = nums.back();
            nums[i] = bkn;
            nums.pop_back();
            n2is[bkn.first][bkn.second] = i;
        }
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int i = rand() % nums.size();
        return nums[i].first;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
