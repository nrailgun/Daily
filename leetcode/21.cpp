class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode root(0);
        ListNode *n, *last = &root;
        
        if (!l1)
            return l2;
        else if (!l2)
            return l1;
        
        while (l1 && l2) {
            if (l1->val < l2->val) {
                n = l1;
                l1 = l1->next;
            } else {
                n = l2;
                l2 = l2->next;
            }
            last->next = n; // Use dummy node to avoid `if`
            last = n;
        }
        
        n->next = l1 ? l1 : l2;
        return root.next;
    }
};
