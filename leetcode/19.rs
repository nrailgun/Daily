impl Solution {
    fn help(head: Option<Box<ListNode>>, n: i32) -> (Option<Box<ListNode>>, i32) {
        match head {
            None => {
                return (None, 0);
            }
            Some(box_) => {
                let v = box_.val;
                let (nxt, i) = Self::help(box_.next, n);
                if i + 1 == n {
                    return (nxt, i + 1);
                } else {
                    let newn = Some(Box::new(
                        ListNode {
                            val: v,
                            next: nxt,
                        }
                    ));
                    return (newn, i + 1);
                }
            }
        }
    }

    pub fn remove_nth_from_end(head: Option<Box<ListNode>>, n: i32) -> Option<Box<ListNode>> {
        let (x, _) = Self::help(head, n);
        return x;
    }
}
