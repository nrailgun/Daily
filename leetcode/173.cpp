// 熟悉 inorder preorder postorder 非递归实现即可。

class BSTIterator {
public:
	stack<TreeNode *> s;

	BSTIterator(TreeNode *root) {
		while (root) {
			s.push(root);
			root = root->left;
		}
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		TreeNode *cur = s.top();
		s.pop();
		int v = cur->val;
		
		cur = cur->right;
		while (cur) {
			s.push(cur);
			cur = cur->left;
		}
		return v;
	}
};
