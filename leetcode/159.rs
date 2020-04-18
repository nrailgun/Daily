use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, LinkedList, VecDeque};
use std::fmt::{Debug, Display};
use std::hash::{BuildHasher, Hash, Hasher};
use std::iter::{repeat, Iterator};
use std::mem::{replace, swap, transmute, transmute_copy};
use std::ptr;
use std::rc::{Rc, Weak};
use std::{i32, i64, u32, u64, u8, usize};

impl Solution {
    pub fn length_of_longest_substring_two_distinct(s: String) -> i32 {
        let n = s.len();
        let b = s.as_bytes();
        let mut i = 0;
        let mut j = i + 1;
        let mut last_c1 = 0;
        let mut max_l = 0;

        while i < n {
            let c1 = b[i];
            let mut c2 = None;
            let mut last_c2 = n; // invalid

            'L: while j < n {
                if b[j] == c1 {
                    last_c1 = j;
                } else {
                    match c2 {
                        None => {
                            c2 = Some(b[j]);
                            last_c2 = j;
                        }
                        Some(_c2) => {
                            if b[j] == _c2 {
                                last_c2 = j;
                            } else {
                                break 'L;
                            }
                        }
                    }
                }
                j += 1;
            }

            max_l = max(max_l, j - i);

            if last_c1 < last_c2 {
                i = last_c1 + 1;
                last_c1 = last_c2;
            } else {
                i = last_c2 + 1;
            }
        }
        return max_l as i32;
    }
}
