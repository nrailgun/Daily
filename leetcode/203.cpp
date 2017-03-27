// Straight forward approach.
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *cur = head, *last = NULL;
        
        while (cur != NULL) {
            if (cur->val != val) {
                last = cur;
                cur = cur->next;
            } else {
                if (last)
                    last->next = cur->next;
                else
                    head = cur->next;
                cur = cur->next;
            }
        }
        return head;
    }
};

// Linus's "elegant" way.
class Solution {
public:
  ListNode* removeElements(ListNode* head, int val) {
    ListNode **pp = &head;
    while (*pp) {
      if ((*pp)->val == val) {
        *pp = (*pp)->next;
      } else {
        pp = &(*pp)->next;
      }
    }
    return head;
  }
};
