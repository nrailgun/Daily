class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode ll(0), gl(0);
        ListNode *lt = &ll, *gt = &gl;
        
        while (head) {
            if (head->val < x) {
                lt->next = head;
                lt = head;
            } else {
                gt->next = head;
                gt = head;
            }
            head = head->next;
        }
        
        lt->next = gl.next;
        gt->next = NULL;
        return ll.next;
    }
};
