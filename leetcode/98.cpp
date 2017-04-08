class Solution {
public:
	bool isValidBST(TreeNode* root, int *pmin = NULL, int *pmax = NULL) {
		if (!root)
			return true;
		if (pmin)
			*pmin = root->val;
		if (pmax)
			*pmax = root->val;

		if (root->left) {
			int minv, maxv;
			if (!isValidBST(root->left, &minv, &maxv))
				return false;
			
			if (maxv >= root->val)
				return false;
			if (pmin)
				*pmin = minv;
		}

		if (root->right) {
			int minv, maxv;
			if (!isValidBST(root->right, &minv, &maxv))
				return false;

			if (minv <= root->val)
				return false;
			if (pmax)
				*pmax = maxv;
		}
		return true;
	}
};
