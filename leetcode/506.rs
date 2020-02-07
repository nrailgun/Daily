use std::cell::{BorrowMutError, Cell, Ref, RefMut, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::i32;
use std::mem::swap;
use std::rc::Rc;
use std::iter::repeat;

impl Solution {
    pub fn find_relative_ranks(a: Vec<i32>) -> Vec<String> {
        let n = a.len();
        let mut b = Vec::with_capacity(n);
        for i in 0..n {
            b.push((i, a[i]));
        }
        b.sort_by(|(_, ai), (_, aj)| aj.cmp(&ai));

        let mut ss: Vec<String> = repeat(String::new()).take(n).collect();
        for i in 0..n {
            let (aid, _) = b[i];
            ss[aid] = {
                match i {
                    0 => "Gold Medal".to_string(),
                    1 => "Silver Medal".to_string(),
                    2 => "Bronze Medal".to_string(),
                    _ => (i + 1).to_string(),
                }
            };
        }
        return ss;
    }
}
