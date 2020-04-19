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
	fn parse(s: &[char]) -> (i32, &[char]) {
		let n = s.len();
		if n == 0 {
			return (0, s);
		}
		let beg = if s[0] == '.' { 1 } else { 0 };
		let mut end = beg + 1;
		while end < n && s[end] != '.' {
			end += 1;
		}
		let ss: String = s[beg..end].iter().collect();
		return (ss.parse::<i32>().unwrap(), &s[end..]);
	}

	fn cmp(v1: &[char], v2: &[char]) -> Ordering {
		let (num1, v1) = Self::parse(v1);
		let (num2, v2) = Self::parse(v2);
		let ord = num1.cmp(&num2);
		return if ord != Ordering::Equal {
			ord
		} else {
			if v1.len() == 0 && v2.len() == 0 {
				ord
			} else {
				Self::cmp(v1, v2)
			}
		};
	}

	pub fn compare_version(version1: String, version2: String) -> i32 {
		let v1: Vec<_> = version1.chars().collect();
		let v2: Vec<_> = version2.chars().collect();
		match Self::cmp(&v1, &v2) {
			Ordering::Equal => 0,
			Ordering::Less => -1,
			Ordering::Greater => 1,
		}
	}
}
