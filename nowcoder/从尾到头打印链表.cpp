/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> v;
        v.reserve(1024);
        while (head) {
            v.push_back(head->val);
            head = head->next;
        }
        reverse(v.begin(), v.end());
        return v;
    }
};
