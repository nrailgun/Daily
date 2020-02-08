use std::cell::{BorrowMutError, Cell, Ref, RefMut, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::i32;
use std::mem::swap;
use std::rc::Rc;
use std::iter::repeat;

impl Solution {
    pub fn add_two_numbers(l1: Option<Box<ListNode>>, l2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        let (mut rl1, mut rl2) = (&l1, &l2);
        let mut head: Option<Box<_>> = Some(Box::new(ListNode {
            val: 0,
            next: None,
        }));
        let mut prev: &mut Option<Box<_>> = &mut head;
        let mut carry = 0;

        loop {
            let (mut c1, mut c2) = (false, false);
            let v1 = match rl1 {
                None => {
                    c1 = true;
                    0
                }
                Some(ref bn) => {
                    rl1 = &(*bn).next;
                    bn.val
                }
            };
            let v2 = match rl2 {
                None => {
                    c2 = true;
                    0
                }
                Some(ref bn) => {
                    rl2 = &(*bn).next;
                    bn.val
                }
            };
            if c1 && c2 && carry == 0 {
                break;
            }

            let v3 = v1 + v2 + carry;
            carry = v3 / 10;
            let new = Some(Box::new(ListNode {
                val: v3 % 10,
                next: None,
            }));

            let bln: &mut Box<ListNode> = prev.as_mut().unwrap();
            bln.next = new;
            prev = &mut bln.next;
        }
        return head.unwrap().next;
    }
}
