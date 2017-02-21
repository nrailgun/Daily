// `multiset` + double pointer.

class TwoSum {
public:
    multiset<int> is;

    /** Add the number to an internal data structure.. */
    void add(int number) {
        is.insert(number);
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        if (is.size() == 0)
            return false;
        
        multiset<int>::iterator i, j;
        i = is.begin();
        j = is.end();
        j--;
        
        while (i != j) {
            int vs = *i + *j;
            if (vs == value)
                return true;
            else if (vs > value)
                j--;
            else
                i++;
        }
        return false;
    }
};
