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
    ListNode* plusOne(ListNode* head) {
        bool c;
        plusOne(head, c);
        if (!c)
            return head;
        else {
            ListNode *h = new ListNode(1);
            h->next = head;
            return h;
        }
    }

    void plusOne(ListNode* head, bool &carry) {
        bool c = true;
        if (head->next) {
            plusOne(head->next, c);
        }
        if (c && ++head->val == 10) {
            head->val = 0;
            carry = true;
        } else {
            carry = false;
        }
    }
};
