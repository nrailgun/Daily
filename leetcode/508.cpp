// 这是一个典型的统计问题。一般统计众数通过在 O(n) 时间计数完成，并一边记录最大的频数。
class Solution {
public:
    unordered_map<int, int> counts;
    int maxfreq;
    
    Solution() : maxfreq(0) {
    }

    int treesum(TreeNode *n) {
        if (!n)
            return 0;
        int ts = n->val + treesum(n->left) + treesum(n->right);
        if (++counts[ts] > maxfreq) // 一边计数一边统计，避免重新循环寻找最大值。
            maxfreq = counts[ts];
        return ts;
    }

    vector<int> findFrequentTreeSum(TreeNode* root) {
        treesum(root);
        vector<int> ss;
        for (auto it = counts.begin(); it != counts.end(); it++) {
            if (it->second == maxfreq)
                ss.push_back(it->first);
        }
        return ss;
    }
};
