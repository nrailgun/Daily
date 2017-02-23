// 算法比较简单，细节可以优化。

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *root = NULL, *last = NULL;
        
        int a = 0;
        while (l1 || l2) {
            int nv = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + a;
            a = nv / 10;
            nv = nv % 10;
            
            ListNode *nn = new ListNode(nv);
            if (!root)
                root = nn;
            if (last)
                last->next = nn;
            last = nn;
            
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        
        if (a) {
            ListNode *nn = new ListNode(a);
            last->next = nn;
        }
        return root;
    }
};

// 通过冗余节点减少 if 跳转
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *root = new ListNode(0); // 冗余节点
        ListNode *last = root;
        
        int a = 0;
        while (l1 || l2) {
            int nv = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + a;
            a = nv / 10;
            nv = nv % 10;
            
            ListNode *nn = new ListNode(nv);
            last->next = nn; // 冗余节点减少一个 if
            last = nn;

            if (l1) // 比 l1 = l1 ? l1->next : NULL 更快
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        
        if (a)
            last->next = new ListNode(a);
        return root->next;
    }
};

// 这个 pool 的想法行不通。因为 test code 会 delete 这些节点导致和 new char [] 不一致而 double free。
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *root = new ListNode(0); // 冗余节点
        ListNode *last = root;
        
        int len = 1, poolnext = 0;
        ListNode *tl1 = l1, *tl2 = l2;
        while (tl1 || tl2) {
            len++;
            if (tl1)
                tl1 = tl1->next;
            if (tl2)
                tl2 = tl2->next;
        }
        ListNode *pool = (ListNode *) new char [sizeof(ListNode) * len];
        
        int a = 0;
        while (l1 || l2) {
            int nv = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + a;
            a = nv / 10;
            nv = nv % 10;
            
            //ListNode *nn = new ListNode(nv);
            ListNode *nn = &(pool[poolnext++]);
            last->next = nn; // 冗余节点减少一个 if
            last = nn;

            if (l1) // 比 l1 = l1 ? l1->next : NULL 更快
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
        }
        
        if (a)
            //last->next = new ListNode(a);
            last->next = &(pool[poolnext++]);
        return root->next;
    }
};
