class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head)
            return NULL;
        
        ListNode *n = head;
        int i = 0;
        while (i < k && n) {
            n = n->next;
            i++;
        }
        if (i < k)
            return head;
        ListNode *last = reverseKGroup(n, k);
        
        ListNode *cur = head;
        while (cur != n) {
            ListNode *tmp = cur->next;
            cur->next = last;
            last = cur;
            cur = tmp;
        }
        return last;
    }
};
