use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, LinkedList, VecDeque};
use std::fmt::{Debug, Display};
use std::hash::{BuildHasher, Hash, Hasher};
use std::iter::{repeat, Iterator};
use std::mem::{replace, swap, take, transmute, transmute_copy};
use std::ptr;
use std::rc::{Rc, Weak};
use std::{i32, i64, u32, u64, u8, usize};

impl Solution {
	fn wtf(root: Rc<RefCell<TreeNode>>) -> (Rc<RefCell<TreeNode>>, Rc<RefCell<TreeNode>>) {
		let mut ref_mut = root.borrow_mut();
		return match ref_mut.left.take() {
			None => {
				(root.clone(), root.clone())
			}
			Some(l) => {
				let r = ref_mut.right.take();
				let (n, p) = Self::wtf(l);
				p.borrow_mut().left = r;
				p.borrow_mut().right.replace(root.clone());
				(n, root.clone())
			}
		};
	}

	pub fn upside_down_binary_tree(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
		match root {
			None => None,
			Some(rc) => {
				let (n, _) = Self::wtf(rc);
				Some(n)
			}
		}
	}
}
