class MovingAverage {
public:
    list<double> l;
    int wsize;
    double mean;

    /** Initialize your data structure here. */
    MovingAverage(int size)
    : wsize(size), mean(0) {
    }
    
    double next(int val) {
        if (l.size() < wsize) {
            l.push_back(val);
            mean = accumulate(l.begin(), l.end(), 0);
            mean = mean / l.size();
            return mean;
        } else {
            double hv = l.front();
            l.erase(l.begin());
            l.push_back(val);
            mean -= hv / wsize;
            mean += (double) val / wsize;
            return mean;
        }
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */
