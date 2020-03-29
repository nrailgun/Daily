use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{repeat, FromIterator, IntoIterator, Iterator};
use std::mem::swap;
use std::rc::Rc;
use std::{i32, i64, u32, u8};

impl Solution {
    fn wtf(root: &mut Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        return match root {
            None => None,
            Some(rc) => {
                let mut ref_ = rc.borrow_mut();
                let (mut lt, mut rt) = (ref_.left.clone(), ref_.right.clone());
                ref_.left = None;
                let (ll, rl) = (Self::wtf(&mut lt), Self::wtf(&mut rt));
                if ll.is_some() {
                    ll.as_ref().unwrap().borrow_mut().right = rt;
                    ref_.right = lt;
                } else {
                    ref_.right = rt;
                }
                if rl.is_some() {
                    rl
                } else if ll.is_some() {
                    ll
                } else {
                    Some(rc.clone())
                }
            }
        };
    }

    pub fn flatten(root: &mut Option<Rc<RefCell<TreeNode>>>) {
        let _ = Self::wtf(root);
    }
}
