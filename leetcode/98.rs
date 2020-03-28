use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{repeat, FromIterator, IntoIterator, Iterator};
use std::mem::swap;
use std::ops::Deref;
use std::rc::Rc;
use std::{i32, i64, u32, u8};

impl Solution {
    fn wtf(root: Option<Rc<RefCell<TreeNode>>>, lb: i64, ub: i64) -> bool {
        match root {
            None => {
                return true;
            }
            Some(rc) => {
                let x: Ref<_> = rc.borrow();
                let xv = x.val as i64;
                if xv <= lb || xv >= ub {
                    return false;
                }
                let lb = Self::wtf(x.left.clone(), lb, xv);
                if !lb {
                    return false;
                }
                return Self::wtf(x.right.clone(), xv, ub);
            }
        }
    }

    pub fn is_valid_bst(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
        Self::wtf(root, i64::MIN, i64::MAX)
    }
}
