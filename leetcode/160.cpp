// Naive idea. Get length, skip some nodes, compare till the same node.

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *l1 = headA;
        int n1 = 0;
        while (l1) {
            n1++;
            l1 = l1->next;
        }
        ListNode *l2 = headB;
        int n2 = 0;
        while (l2) {
            n2++;
            l2 = l2->next;
        }
        
        int skip = abs(n1 - n2);
        if (n1 < n2) {
            l1 = headA;
            l2 = headB;
        } else {
            l1 = headB;
            l2 = headA;
        }
        while (skip--) {
            l2 = l2->next;
        }
        
        while (l1 && l2 && l1 != l2) {
            l1 = l1->next;
            l2 = l2->next;
        }
        return l1;
    }
};

// 聪明的想法。如果两者有 intersection，等长，必然出现 l1==l2，不等长，通过交换指针相当于跳过了若干长度。
// 虽然复杂度是一样的。
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB)
            return NULL;
        
        ListNode *l1 = headA, *l2 = headB;
        while (l1 != l2) {
            l1 = l1 ? l1->next : headB;
            l2 = l2 ? l2->next : headA;
        }
        return l1;
    }
};
