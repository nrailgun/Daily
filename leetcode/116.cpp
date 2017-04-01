class Solution {
public:
  void connect(TreeLinkNode *root) {
    if (!root)
      return;
    root->next = NULL;

    TreeLinkNode *head = root, *cur;
    for (cur = head; cur != NULL; ) {
      if (!cur->left)
        break;
      cur->left->next = cur->right;
      if (cur->next) {
        cur->right->next = cur->next->left;
        cur = cur->next;
      }
      else {
        cur->right->next = NULL;
        cur = (head = head->left);
      }
    }
  }
};
