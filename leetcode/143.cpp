
class Solution {
public:
	ListNode *wtf(ListNode *cur, int i, int l) {
		if (l % 2 == 1 && i == l / 2) {
			ListNode *nxt = cur->next;
			cur->next = NULL;
			return nxt;
		}
		else if (l % 2 == 0 && i + 1 == l / 2) {
			ListNode *nxt1 = cur->next;
			ListNode *nxt2 = nxt1->next;
			nxt1->next = NULL;
			return nxt2;
		}
		else {
			ListNode *nxt1 = cur->next;
			ListNode *nxt2 = wtf(nxt1, i + 1, l);
			ListNode *nxt3 = nxt2->next;
			nxt2->next = nxt1;
			cur->next = nxt2;
			return nxt3;
		}
	}

	void reorderList(ListNode* head) {
		int l = 0;
		ListNode *n = head;
		while (n) {
			l++;
			n = n->next;
		}
		if (l <= 2) {
			return;
		}
		wtf(head, 0, l);
	}
};
