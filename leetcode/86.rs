use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{repeat, FromIterator, IntoIterator, Iterator};
use std::mem::swap;
use std::ops::Deref;
use std::rc::Rc;
use std::{i32, i64, u32, u8};

impl Solution {
    fn fuck(h: Option<Box<ListNode>>, x: i32) -> (Option<Box<ListNode>>, Option<Box<ListNode>>) {
        return match h {
            None => (None, None),
            Some(mut box_) => {
                let nxt = box_.next;
                box_.next = None;

                let (la, lb) = Self::fuck(nxt, x);
                if box_.val < x {
                    box_.next = la;
                    (Some(box_), lb)
                } else {
                    box_.next = lb;
                    (la, Some(box_))
                }
            }
        };
    }

    fn concat(mut la: Option<Box<ListNode>>, lb: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        if la.is_none() {
            return lb;
        }
        let mut p: &mut Box<_> = la.as_mut().unwrap();
        while p.next.is_some() {
            p = p.next.as_mut().unwrap();
        }
        p.next = lb;
        return la;
    }

    pub fn partition(h: Option<Box<ListNode>>, x: i32) -> Option<Box<ListNode>> {
        let (la, lb) = Self::fuck(h, x);
        let lc = Self::concat(la, lb);
        return lc;
    }
}
