use std::{i32, i64, u32, u8};
use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{FromIterator, IntoIterator, Iterator, once, repeat};
use std::mem::{replace, swap};
use std::rc::Rc;

impl Solution {
    fn wtf(cur: Option<Box<ListNode>>, i: usize, l: usize) -> (Option<Box<ListNode>>, Option<Box<ListNode>>) {
        let mut box_: Box<_> = cur.unwrap();
        return if l % 2 == 0 && i == l / 2 {
            let nxt1: Option<Box<_>> = box_.next.take();
            (Some(box_), nxt1)
        } else if l % 2 == 1 && i == l / 2 + 1 {
            (None, Some(box_))
        } else {
            let nxt1: Option<Box<_>> = box_.next.take();
            let (nxt2, mut nxt3) = Self::wtf(nxt1, i + 1, l);
            box_.next = nxt2;
            match nxt3.as_mut() {
                None => {
                    (Some(box_), None)
                }
                Some(box3) => {
                    // 注意这里，如果不进行 take，那么 box3 会被当成 moved。其他类型可以用 replace / swap 换一个 empty 上去。
                    let nxt4 = box3.next.take();
                    box3.next = Some(box_);
                    (nxt3, nxt4)
                }
            }
        }
    }

    pub fn reorder_list(head: &mut Option<Box<ListNode>>) {
        let mut l = 0;
        let mut cur = head.as_ref();
        while let Some(x) = cur {
            l += 1;
            cur = x.next.as_ref();
        }
        if l < 2 {
            return;
        }
        let h: Option<Box<_>> = head.take(); // 注意要把所有权夺过来。
        let (h, _) = Self::wtf(h, 0, l);
        replace(head, h);
    }
}
