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
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode *cur = head, *tail = NULL;
        int n = 0;
        
        while (cur) {
            n++;
            tail = cur;
            cur = cur->next;
        }
        if (n == 0)
            return head;
        k %= n;
        if (k == 0)
            return head;
        
        ListNode *slow = head, *fast = head;
        for (int i = 0; i < k; i++)
            fast = fast->next;
        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        fast->next = head;
        head = slow->next;
        slow->next = NULL;
        return head;
    }
};
