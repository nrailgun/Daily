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

// O(1) 空间。
