// 思路是这么个思路，怎么 rust 操作数据结构就这么蛋疼呢...

use std::cell::{BorrowMutError, Cell, Ref, RefMut, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::i32;
use std::mem::swap;
use std::rc::Rc;

impl Solution {
    fn inorder(root: &Option<Rc<RefCell<TreeNode>>>) -> Vec<Rc<RefCell<TreeNode>>> {
        let mut v = vec![];
        if root.is_none() {
            return v;
        }
        let mut st: Vec<(Rc<RefCell<_>>, bool)> = vec![(root.as_ref().unwrap().clone(), false)];

        while !st.is_empty() {
            let (rc, expanded): (Rc<RefCell<_>>, _) = st.pop().unwrap();
            if expanded {
                v.push(rc);
            } else {
                let ref_: Ref<_> = (*rc).borrow();
                if ref_.right.is_some() {
                    st.push((ref_.right.as_ref().unwrap().clone(), false));
                };
                st.push((rc.clone(), true));
                if ref_.left.is_some() {
                    st.push((ref_.left.as_ref().unwrap().clone(), false));
                };
            }
        }
        return v;
    }

    pub fn recover_tree(root: &mut Option<Rc<RefCell<TreeNode>>>) {
        let inorder: Vec<Rc<RefCell<_>>> = Self::inorder(root);
        let n = inorder.len();
        let mut is = vec![];
        for i in 0..n - 1 {
            let v1 = inorder[i].borrow().val;
            let v2 = inorder[i + 1].borrow().val;
            if v1 > v2 {
                is.push(i);
            }
        }

        if is.len() == 1 {
            let i1 = is[0];
            let rc1 = inorder[i1].clone();
            let mut ref1: RefMut<_> = rc1.borrow_mut();
            let rc2 = inorder[i1 + 1].clone();
            let mut ref2: RefMut<_> = rc2.borrow_mut();
            swap(&mut ref1.val, &mut ref2.val);
        } else if is.len() == 2 {
            let i1 = is[0];
            let rc1 = inorder[i1].clone();
            let mut ref1: RefMut<_> = rc1.borrow_mut();
            let i2 = is[1] + 1;
            let rc2 = inorder[i2].clone();
            let mut ref2: RefMut<_> = rc2.borrow_mut();
            swap(&mut ref1.val, &mut ref2.val);
        } else {
            unreachable!();
        }
    }
}
