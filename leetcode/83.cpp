class Solution {
public:
  ListNode* deleteDuplicates(ListNode* head) {
    ListNode *n = head;
    while (n) {
      while (n->next && n->next->val == n->val)
        n->next = n->next->next;
      n = n->next;
    }
    return head;
  }
};
