class NestedIterator {
public:
    vector<int> v;
    int idx;

    void putv(const vector<NestedInteger> &nl) {
        for (auto ni : nl) {
            if (ni.isInteger()) {
                v.push_back(ni.getInteger());
            } else {
                putv(ni.getList());
            }
        }
    }

    NestedIterator(const vector<NestedInteger> &nestedList) : idx(0) {
        putv(nestedList);
    }

    int next() {
        return v[idx++];
    }

    bool hasNext() {
        return idx < v.size();
    }
};
