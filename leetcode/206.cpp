class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head)
            return NULL;
            
        ListNode *last = NULL;
        while (head) {
            ListNode *tmp = head->next;
            head->next = last;
            last = head;
            head = tmp;
        }
        return last;
    }
};
