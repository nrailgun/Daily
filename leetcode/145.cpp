// Iterative post order traversal.

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> v;
        stack<TreeNode *> st;
        TreeNode *cur = root, *last = nullptr;
        
        while (cur || !st.empty()) {
            if (cur) {
                st.push(cur);
                cur = cur->left;
            } else {
                cur = st.top();
                // 利用 last 这个标记指针来处理 postorder
                if (cur->right && cur->right != last) {
                    cur = cur->right;
                } else {
                    st.pop();
                    v.push_back(cur->val);
                    last = cur;
                    cur = nullptr;
                }
            }
        }
        return v;
    }
};
