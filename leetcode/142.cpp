// 我只想说 WTF。

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head)
            return NULL;
        ListNode *slow = head, *fast = head;
        
        do {
            slow = slow->next;
            if (fast && fast->next)
                fast = fast->next->next;
            else
                return NULL;
        } while (slow != fast);

        ListNode *entry = head;
        while (entry != slow) {
            entry = entry->next;
            slow = slow->next;
        }
        return entry;
    }
};
