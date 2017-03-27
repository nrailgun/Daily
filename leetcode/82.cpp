class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode h(0);
        h.next = head;
        ListNode *cur = &h;
        
        while (cur) {
            ListNode *nxt = cur->next;
            if (nxt && nxt->next && nxt->val == nxt->next->val) {
                int v = nxt->val;
                while (nxt && nxt->val == v)
                    nxt = nxt->next;
                cur->next = nxt;
            } else
                cur = cur->next;
        }
        return h.next;
    }
};
