class Solution {
public:
    
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        
        int n = matrix.size();
        vector<int> is(n, 0);
        for (int i = 0; i < n; i++) {
            if (matrix[i].empty())
                continue;
            q.push(make_pair(matrix[i][0], i));
        }
        
        for (int i = 0; i < k; i++) {
            pair<int, int> p = q.top();
            if (i == k - 1)
                return p.first;
            q.pop();
            
            int idx = p.second;
            if (++is[idx] < matrix[idx].size()) {
                q.push(make_pair( matrix[idx][is[idx]], idx ));
            }
        }
    }
};
