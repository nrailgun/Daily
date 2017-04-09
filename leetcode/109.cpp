class Solution {
public:
	TreeNode *solve(ListNode *&n, int beg, int end) {
		if (!n)
			return NULL;
		if (beg > end)
			return NULL;

		int mid = (end + beg) / 2;

		TreeNode *left = solve(n, beg, mid - 1);
		TreeNode *t = new TreeNode(n->val);
		
    // 此处是精髓，避免了每次递归 o(n) 寻找中点的时间代价，直接总时间代价 O(n log n) -> O(log n)。
    // 简直不要太机智。
    n = n->next;
		
    TreeNode *right = solve(n, mid + 1, end);
		t->left = left;
		t->right = right;
		return t;
	}

	TreeNode* sortedListToBST(ListNode* head) {
		int sz = 0;
		ListNode *n = head;
		while (n) {
			sz++;
			n = n->next;
		}
		return solve(head, 0, sz - 1);
	}
};
