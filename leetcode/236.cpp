class Solution {
public:
	int lca(TreeNode *root, TreeNode *p, TreeNode *q, TreeNode **out) {
		if (!root) {
			return 0;
		}
		else if (!root->left && !root->right) {
			if (root == p || root == q) {
				return 1;
			}
			else {
				return 0;
			};
		}
		else {
			int cl = lca(root->left, p, q, out);
			if (cl == 2) {
				return 2;
			}
			int cr = lca(root->right, p, q, out);
			if (cr == 2) {
				return 2;
			}

			if (cl + cr == 2) {
				*out = root;
				return 2;
			}
			else {
				if (root == p || root == q) {
					if (cl + cr == 1) {
						*out = root;
						return 2;
					}
					else {
						return 1;
					}
				}
				else {
					return cl + cr;
				}
			}
		}
	}

	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		TreeNode *rv = nullptr;
		lca(root, p, q, &rv);
		return rv;
	}
};
