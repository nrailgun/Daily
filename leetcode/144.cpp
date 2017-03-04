// Iterative preorder traversal.
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> v;
        stack<TreeNode *> st;
        TreeNode *cur = root;
        while (cur || !st.empty()) {
            if (cur) {
                v.push_back(cur->val);
                st.push(cur);
                cur = cur->left;
            } else {
                cur = st.top();
                st.pop();
                cur = cur->right;
            }
        }
        return v;
    }
};

