impl Solution {
    //noinspection RsBorrowChecker
    pub fn reverse_between(mut h: Option<Box<ListNode>>, m: i32, n: i32) -> Option<Box<ListNode>> {
        let mut a = vec![];
        'L: loop {
            match h {
                None => {
                    break 'L;
                }
                Some(mut box_) => {
                    h = box_.next;
                    box_.next = None;
                    a.push(box_);
                }
            }
        }
        {
            let s = &mut a[(m as usize - 1)..(n as usize)];
            s.reverse();
        }

        let mut last = None;
        for mut i in a.into_iter().rev() {
            i.next = last;
            last = Some(i);
        }
        return last;
    }
}
