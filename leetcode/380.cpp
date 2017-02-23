class RandomizedSet {
public:
    unordered_map<int, int> um;
    vector<int> iv;

    /** Initialize your data structure here. */
    RandomizedSet() {
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        auto it = um.find(val);
        if (it != um.end())
            return false;
        
        um[val] = iv.size();
        iv.push_back(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        auto it = um.find(val);
        if (it == um.end())
            return false;
        
        int idx = it->second;
        swap(iv[idx], iv[iv.size()-1]);
        iv.pop_back();
        
        um[iv[idx]] = idx;
        um.erase(it);
        
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return iv[rand() % iv.size()];
    }
};
