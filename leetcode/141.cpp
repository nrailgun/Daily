class Solution {
public:
    bool hasCycle(ListNode *head) {
        const ListNode *slow, *fast;
        
        slow = head;
        fast = head;
        while (true) {
            if (slow) {
                slow = slow->next;
            } else
                return false;
            
            if (fast && fast->next) {
                fast = fast->next->next;
            } else
                return false;
                
            if (fast == slow)
                return true;
        }
        return false;
    }
};
