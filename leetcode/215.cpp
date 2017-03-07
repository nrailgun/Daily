// K-th large number. Em, old enough.

class Solution {
public:
    int findKthLargest(vector<int>& ns, int k) {
        int n = ns.size();
        priority_queue<int, vector<int>, greater<int>> pq;
        
        for (auto i : ns) {
            pq.push(i);
            if (pq.size() == k + 1)
                pq.pop();
        }
        return pq.top();
    }
};
