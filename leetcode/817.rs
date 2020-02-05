// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
// 
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }

use std::borrow::Borrow;
use std::cell::{BorrowMutError, Cell, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet};
use std::i32;
use std::iter::{Iterator, FromIterator};
use std::ops::Deref;
use std::rc::Rc;
use std::sync::{Arc, Mutex};

impl Solution {
    pub fn num_components(h: Option<Box<ListNode>>, g: Vec<i32>) -> i32 {
        let mut s: HashSet<i32> = g.iter().cloned().collect();
        let mut rv = 0;
        let mut dc = true;

        let mut x = h;
        while x.is_some() {
            let y = x.unwrap();
            if !s.contains(&y.val) {
                dc = true;
            } else {
                s.remove(&y.val);
                if dc {
                    dc = false;
                    rv += 1;
                }
            }
            x = y.next;
        }
        return rv;
    }
}
