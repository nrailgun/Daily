use std::cell::{BorrowMutError, Cell, Ref, RefMut, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::iter::{Iterator, FromIterator};
use std::mem::swap;
use std::rc::Rc;
use std::{i32, u32, i64, f32, f64};

impl Solution {
    fn bound(a: &[i32], tg: i32, lower: bool) -> i32 {
        let n = a.len();
        if n == 0 {
            return -1;
        }

        let (mut lb, mut ub) = (0, n - 1);
        loop {
            if lb == ub {
                return {
                    if a[lb] == tg {
                        lb as i32
                    } else {
                        -1
                    }
                };
            }

            let mid = (lb + ub) / 2;
            match a[mid].cmp(&tg) {
                Ordering::Equal => {
                    // 如果找到了就向着两侧继续二分查找。
                    return {
                        if lower {
                            let x = Self::bound(&a[..mid], tg, lower);
                            if x == -1 { mid as i32 } else { x }
                        } else {
                            let x = Self::bound(&a[mid + 1..], tg, lower);
                            if x == -1 { mid as i32 } else { mid as i32 + 1 + x }
                        }
                    };
                }
                Ordering::Less => {
                    lb = mid + 1;
                }
                Ordering::Greater => {
                    ub = mid;
                }
            }
        }
    }

    pub fn search_range(a: Vec<i32>, tg: i32) -> Vec<i32> {
        let lb = Self::bound(&a, tg, true);
        let ub = Self::bound(&a, tg, false);
        return vec![lb, ub];
    }
}
