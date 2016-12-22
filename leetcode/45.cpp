// Naive approach: DFS, time limit exceeded.
class Solution {
public:
    int n;
    vector<int> min_steps;

    int min_step(vector<int> &nums, int posi) {
        int n = nums.size();
        
        if (min_steps[posi] > 0)
            return min_steps[posi];
        
        if (posi == n - 1)
            return 0;
        
        int minstep = INT_MAX;
        for (int i = posi + 1; i < n && i <= posi + nums[posi]; i++) {
            int tmp = min_step(nums, i);
            if (tmp != INT_MAX)
                minstep = min(minstep, 1 + tmp);
        }
        return min_steps[posi] = minstep;
    }

    int jump(vector<int>& nums) {
        n = nums.size();
        min_steps.resize(n);
        fill(min_steps.begin(), min_steps.end(), -1);
    
        return min_step(nums, 0);
    }
};

// BFS wouldn't work for certain.
class Solution {
public:
    typedef pair<int, int> E; // (index, step)

    int jump(vector<int>& nums) {
        int n = nums.size();
        queue<E> q;
        q.push(E(0, 0));
        
        while (!q.empty()) {
            E e = q.front();
            q.pop();
            
            int idx = e.first, step = e.second;
            if (idx == n - 1)
                return step;
            
            for (int i = idx + 1; i <= idx + nums[idx]; i++) {
                E newe(i, step + 1);
                q.push(newe);
            }
        }
        return INT_MAX;
    }
};
