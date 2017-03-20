// 这个傻x题目其实是个智力题，实际删除的是下一个节点。

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
    void deleteNode(ListNode* node) {
        ListNode *nxt = node->next;
        node->val = nxt->val;
        node->next = nxt->next;
    }
};
