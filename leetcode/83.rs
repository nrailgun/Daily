impl Solution {
    pub fn delete_duplicates(head: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if head.is_none() {
            return None;
        }
        let mut box_ = head.unwrap();
        let mut nxt = box_.next;
        while nxt.is_some() {
            let nxt_box = nxt.unwrap();
            if nxt_box.val == box_.val {
                nxt = nxt_box.next;
            } else {
                nxt = Some(nxt_box); // rustc 可以分析出来如果没有这一句，nxt 是已经被 moved 的，简直 NB。
                break;
            }
        }
        box_.next = Self::delete_duplicates(nxt);
        return Some(box_);
    }
}
