class Solution {
public:
  TreeLinkNode *GetNext(TreeLinkNode *n) {
    if (!n)
      return NULL;

    TreeLinkNode *cur, *p;

    if (n->right) {
      cur = n->right;
      while (cur->left)
        cur = cur->left;
      return cur;
    }

    cur = n;
    p = n->next;
    while (p && cur == p->right) {
      cur = p;
      p = cur->next;
    }
    if (!p)
      return NULL;
    return p;
  }
};
