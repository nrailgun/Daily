// 其实不是 HARD 难度，很多 Easy 都比这难。

class NodeComparator {
public:
  bool operator()(const ListNode *n1, const ListNode *n2) const {
    return n1->val > n2->val;
  }
};

class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    NodeComparator nc;
    priority_queue<ListNode *, vector<ListNode *>, NodeComparator> pq(nc);
    for (ListNode *n : lists) {
      if (n)
        pq.push(n);
    }

    ListNode head(0);
    ListNode *tail = &head;
    while (pq.size() > 1) {
      ListNode *n = pq.top();
      pq.pop();
      tail->next = n;
      tail = n;
      if (n->next)
        pq.push(n->next);
    }
    if (pq.size() > 0)
      tail->next = pq.top();
    return head.next;
  }
};
