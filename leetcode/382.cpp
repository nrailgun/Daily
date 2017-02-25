#if 0
// 储水池采样算法
// S has items to sample, R will contain the result
ReservoirSample(S[1..n], R[1..k])
  // fill the reservoir array
  for i = 1 to k
      R[i] := S[i]

  // replace elements with gradually decreasing probability
  for i = k+1 to n
    j := random(1, i)   // important: inclusive range
    if j <= k
        R[j] := S[i]

// 加权储水池采样算法
(*
  S has items to sample, R will contain the result
  S[i].Weight contains weight for each item
 *)
WeightedReservoir-Chao(S[1..n], R[1..k])
  WSum = 0
  // fill the reservoir array
  for i = 1 to k
      R[i] := S[i]
      WSum = WSum + S[i].Weight/k
  for i = k+1 to n
    WSum = WSum + S[i].Weight/k
    p = S[i].Weight / WSum // probability for this item
    j := random(0, 1);     // important: inclusive range
    if j <= p              // select item according to probability
        R[random(1,k)] := S[i]  //uniform selection in reservoir for replacement
#endif

class Solution {
public:
    const ListNode *head;

    Solution(ListNode* head) {
        this->head = head;
    }
    
    int getRandom() {
        int i = 2, v = head->val;
        const ListNode *node = head->next;
        while (node) {
            int k = rand() % (i++);
            if (k == 0)
                v = node->val;
            node = node->next;
        }
        return v;
    }
};
