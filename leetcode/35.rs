use std::{i32, i64, u32};
use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::iter::{FromIterator, Iterator};
use std::mem::swap;
use std::rc::Rc;

impl Solution {
    fn lower_bound(a: &[i32], tg: i32) -> usize {
        let n = a.len();
        if n == 0 {
            return 0;
        }
        let (mut lb, mut ub) = (0, n - 1);
        while lb < ub {
            let mid = (lb + ub) / 2;
            match a[mid].cmp(&tg) {
                Ordering::Less => {
                    lb = mid + 1;
                }
                Ordering::Greater => {
                    ub = mid;
                }
                Ordering::Equal => {
                    return Self::lower_bound(&a[..mid], tg);
                }
            }
        }
        return {
            if a[lb] < tg {
                lb + 1
            } else {
                lb
            }
        };
    }

    pub fn search_insert(a: Vec<i32>, tg: i32) -> i32 {
        let x = Self::lower_bound(&a, tg);
        return x as i32;
    }
}
