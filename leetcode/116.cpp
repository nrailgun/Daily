class Solution {
public:
  void connect(TreeLinkNode *root) {
    if (!root)
      return;
    root->next = NULL;

    TreeLinkNode *head = root;
    while (head->left) {
      TreeLinkNode *cur = head;
      for ( ; cur != NULL; cur = cur->next) {
        cur->left->next = cur->right;
        if (cur->next)
          cur->right->next = cur->next->left;
        else
          cur->right->next = NULL;
      }
      head = head->left;
    }
  }
};
