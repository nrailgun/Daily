class Solution {
public:
  ListNode *split_list(ListNode *h) {
    ListNode *slow = h, *fast = h->next;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    h = slow->next;
    slow->next = NULL;
    return h;
  }

  ListNode* sortList(ListNode* head) {
    if (!head || !head->next)
      return head;

    ListNode *mid = split_list(head);
    ListNode *l1 = sortList(head);
    ListNode *l2 = sortList(mid);

    ListNode h(0), *tail;
    tail = &h;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        tail->next = l1;
        tail = l1;
        l1 = l1->next;
      } else {
        tail->next = l2;
        tail = l2;
        l2 = l2->next;
      }
    }
    tail->next = l1 ? l1 : l2;
    return h.next;
  }
};
