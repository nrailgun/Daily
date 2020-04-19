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
    pub fn is_one_edit_distance(s: String, t: String) -> bool {
        let ns = s.len();
        let nt = t.len();
        if ns < nt {
            return Self::is_one_edit_distance(t, s);
        }
        let nd = ns - nt;
        let bs = s.as_bytes();
        let bt = t.as_bytes();

        if nd > 1 {
            return false;
        } else if nd == 0 {
            let miss = bs.iter().zip(bt.iter()).fold(0, |acc, (&us, &ut)| {
                if us == ut {
                    acc
                } else {
                    acc + 1
                }
            });
            return miss == 1;
        } else {
            let (mut i, mut j) = (0, 0);
            while i < nt && j < ns {
                if bt[i] == bs[j] {
                    i += 1;
                    j += 1;
                } else {
                    j += 1;
                }
            }
            return i == nt;
        }
    }
}
