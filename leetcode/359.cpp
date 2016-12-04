class Logger {
public:
    map<string, int> m;

    /** Initialize your data structure here. */
    Logger() {
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        map<string, int>::iterator it;
        
        it = m.find(message);
        if (it != m.end()) {
            int &t = it->second;
            if (timestamp - t < 10)
                return false;
            else {
                t = timestamp;
                return true;
            }
        }
        else {
            m[message] = timestamp;
            return true;
        }
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger obj = new Logger();
 * bool param_1 = obj.shouldPrintMessage(timestamp,message);
 */
