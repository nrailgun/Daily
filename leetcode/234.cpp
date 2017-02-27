// O(n) 时间和空间复杂度。
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> v;
        
        while (head) {
            v.push_back(head->val);
            head = head->next;
        }
        
        for (int i = 0; i < v.size() / 2; i++) {
            if (v[i] != v[v.size()-1-i])
                return false;
        }
        return true;
    }
};

// O(1) 空间。找到中点，翻转，顺序比较。我真是太机智了。
// 小心置空指针，免得 leetcode release 出错。
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next)
            return true;
        
        ListNode *mid = head, *fast = head;
        while (fast->next && fast->next->next) {
            mid = mid->next;
            fast = fast->next->next;
        }

        ListNode *last = mid, *n = mid->next;
        while (n) {
            ListNode *tmp = n;
            n = n->next;
            tmp->next = last;
            last = tmp;
        }
        mid->next->next = nullptr; // 无关算法，但是不置空会导致 leetcode 释放出错
        mid->next = nullptr;
        
        ListNode *n1 = head, *n2 = last;
        while (n1 && n2) {
            if (n1->val != n2->val) {
                return false;
            }
            n1 = n1->next;
            n2 = n2->next;
        }
        return true;
    }
};
