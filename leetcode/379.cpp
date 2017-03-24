class PhoneDirectory {
public:
    set<int> avail;
    
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            avail.insert(i);
        }
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if (avail.empty())
            return -1;
        auto it = avail.begin();
        int v = *it;
        avail.erase(it);
        return v;
    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return avail.end() != avail.find(number);
    }
    
    /** Recycle or release a number. */
    void release(int number) {
        avail.insert(number);
    }
};
