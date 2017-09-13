// 两种特殊Case：NULL，无环。第二种简直智障。

class Solution {
public:
  ListNode* EntryNodeOfLoop(ListNode* ph) {
    if (!ph)
      return NULL;

    ListNode *pslow, *pfast;
    pslow = ph;
    pfast = ph;
    do {
      pslow = pslow->next;
      pfast = pfast->next;
      if (!pfast)
        return NULL;
      pfast = pfast->next;
      if (!pfast)
        return NULL;
    } while (pslow != pfast);

    ListNode *meet = pslow;
    int cl = 0;
    do {
      pslow = pslow->next;
      cl++;
    } while (pslow != meet);

    pslow = ph;
    pfast = ph;
    for (int i = 0; i < cl; i++)
      pfast = pfast->next;
    while (pslow != pfast) {
      pslow = pslow->next;
      pfast = pfast->next;
    }
    return pslow;
  }
};
