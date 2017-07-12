// Categorized to BFS on Leetcode. Anyway not trivial search at all.

typedef pair<int, int> Edge;
 
class Solution {
public:
    int n;
    vector<vector<int>> adjl;
    
    vector<int> findMinHeightTrees(int n, const vector<Edge>& edges) {
        this->n = n;
        adjl = vector<vector<int>>(n);
        for (auto e : edges) {
            adjl[e.first].push_back(e.second);
            adjl[e.second].push_back(e.first);
        }
        
        vector<int> roots;
        int minh = INT_MAX;
        
        for (int r = 0; r < n; r++) {
            int h = height(r);
            if (h < minh) {
                roots.clear();
                minh = h;
            }
            if (h == minh) {
                roots.push_back(r);
            }
        }
        return roots;
    }
    
    int height(int root, int from = -1) {
        int minh = INT_MAX;
        
        for (int node : adjl[root]) {
            if (node == from)
                continue;
            int h = height(node, root);
            minh = min(minh, h);
        }
        return minh == INT_MAX ? 1 : minh + 1;
    }
};

// Similar to Topological sort. Remove leaves one by one.

typedef pair<int, int> Edge;

class Solution {
public:
    
    vector<int> findMinHeightTrees(int n, const vector<Edge>& edges) {
        vector<unordered_set<int>> adjs(n);
        vector<int> leaves;
        if (n == 1) {
            leaves.push_back(0);
            return leaves;
        }
        
        for (int i = 0; i < edges.size(); i++) {
            int a = edges[i].first, b = edges[i].second;
            adjs[a].insert(b);
            adjs[b].insert(a);
        }
        for (int i = 0; i < adjs.size(); i++) {
            if (adjs[i].size() == 1)
                leaves.push_back(i);
        }
        
        while (n > 2) {
            n -= leaves.size();
            vector<int> newleaves;
            
            for (int i = 0; i < leaves.size(); i++) {
                int leaf = leaves[i];
                int b = *adjs[leaf].begin();
                adjs[b].erase(leaf);
                if (adjs[b].size() == 1)
                    newleaves.push_back(b);
            }
            leaves = newleaves;
        }
        
        return leaves;
    }
};
