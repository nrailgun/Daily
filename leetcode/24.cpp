/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode h(0);
        h.next = head;
        
        ListNode *cur = &h;
        while (cur) {
            ListNode *n1 = cur->next;
            if (!n1)
                break;
            ListNode *n2 = n1->next;
            if (!n2)
                break;
            
            cur->next = n2;
            n1->next = n2->next;
            n2->next = n1;
            cur = n1;
        }
        return h.next;
    }
};
