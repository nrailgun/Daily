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
    ListNode* insertionSortList(ListNode* head) {
        ListNode *sorted = NULL;
        
        while (head) {
            ListNode *n = head;
            head = head->next;
            n->next = NULL;
            sorted = insert(sorted, n);
        }
        return sorted;
    }
    
    ListNode *insert(ListNode *sorted, ListNode *n) {
        ListNode head(0);
        head.next = sorted;
        
        ListNode *cur = &head;
        while (1) {
            if (!cur->next) {
                cur->next = n;
                return head.next;
            }
            else if (n->val <= cur->next->val) {
                n->next = cur->next;
                cur->next = n;
                return head.next;
            } else {
                cur = cur->next;
            }
        }
        return NULL;
    }
};
