// 机智求解。两个指针逼近。好像和 greedy 没什么关系。

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        
        int start = 0, end = 0;
        int sum = 0;
        while (1) {
            //cout << "start loop" << endl;
            
            while ( (sum += gas[end] - cost[end]) >= 0) {
                end = (end + 1) % n;
                if (end == start)
                    return start;
            }
            //cout << "stop at start = " << start << " end = " << end << " sum = " << sum << endl;

            while (sum < 0) {
                if (--start < 0)
                    start = n - 1;
                if (start == end)
                    return sum >= 0 ? start : -1;
                sum += gas[start] - cost[start];
                //cout << "start = " << start << " end = " << end << " sum = " << sum << endl;
            }
            end++;
        }
    }
};
