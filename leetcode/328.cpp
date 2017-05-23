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
    ListNode* oddEvenList(ListNode* head) {
        ListNode ho(0), he(0);
        ListNode *to = &ho, *te = &he;
        
        int i = 0;
        while (head) {
            if (++i % 2) {
                to->next = head;
                to = head;
                head = head->next;
                to->next = NULL;
            } else {
                te->next = head;
                te = head;
                head = head->next;
                te->next = NULL;
            }
        }
        to->next = he.next;
        return ho.next;
    }
};
