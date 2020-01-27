use std::cell::{Cell, RefCell, BorrowMutError};
use std::rc::Rc;
use std::sync::{Arc, Mutex};
use std::cmp::Ordering;

impl Solution {
    pub fn help(oroot: &Option<Rc<RefCell<TreeNode>>>, depth: usize) -> (usize, i32) {
        match oroot {
            None => {
                return (0, 0);
            }
            Some(root) => {
                let lroot = &root.borrow().left;
                let rroot = &root.borrow().right;
                if lroot.is_none() && rroot.is_none() {
                    return (depth, root.borrow().val);
                }

                let (ld, lsum) = Self::help(lroot, depth + 1);
                let (rd, rsum) = Self::help(rroot, depth + 1);
                return match ld.cmp(&rd) {
                    Ordering::Less => (rd, rsum),
                    Ordering::Greater => (ld, lsum),
                    Ordering::Equal => (ld, lsum + rsum),
                }
            }
        }
    }

    pub fn deepest_leaves_sum(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
        let (_, sum) = Self::help(&root, 0);
        return sum;
    }
}
