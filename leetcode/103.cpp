class Solution {
public:
	typedef enum { L2R = 0, R2L = 1 } Direction;

	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		queue<pair<TreeNode *, int>> q;
		q.push(make_pair(root, 0));

		vector<vector<int>> vv;

		while (!q.empty()) {
			pair<TreeNode *, int> p = q.front();
			q.pop();
			TreeNode *n = p.first;
			int depth = p.second;
			if (!n)
				continue;

			if (depth >= vv.size()) {
				vv.resize(depth + 1);
			}
			vv[depth].push_back(n->val);
			q.push(make_pair(n->left, depth + 1));
			q.push(make_pair(n->right, depth + 1));
		}

		for (int i = 0; i < vv.size(); i++) {
			if (i % 2) {
				reverse(vv[i].begin(), vv[i].end());
			}
		}
		return vv;
	}
};
