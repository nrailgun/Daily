use std::borrow::Borrow;
use std::cell::{BorrowMutError, Cell, Ref, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet};
use std::i32;
use std::iter::{FromIterator, Iterator};
use std::ops::Deref;
use std::rc::Rc;
use std::sync::{Arc, Mutex};

impl Solution {
    fn rob1(root: Option<Rc<RefCell<TreeNode>>>) -> (i32, i32) {
        if root.is_none() {
            return (0, 0);
        }
        let rc: Rc<RefCell<_>> = root.unwrap();
        let ref_: Ref<_> = (*rc).borrow();

        let (lv1, lv2) = Self::rob1(ref_.left.clone());
        let (rv1, rv2) = Self::rob1(ref_.right.clone());
        (ref_.val + lv2 + rv2, max(lv1, lv2) + max(rv1, rv2))
    }

    pub fn rob(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let (v1, v2) = Self::rob1(root);
        max(v1, v2)
    }
}
