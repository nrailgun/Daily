class MovingAverage {
public:
    queue<double> q;
    int k;
    double av;
    
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        k = size;
        av = 0;
    }
    
    double next(int val) {
        int n = q.size();
        if (n < k) { // 此处只需求和，可避免 n < k 时的 */ 运算
            av += val; // av = (av * n + val) / (n + 1);
        } else {
            av += val - q.front();
        }
        
        if (q.size() == k)
            q.pop();
        q.push(val);
        return av / q.size();
    }
};
