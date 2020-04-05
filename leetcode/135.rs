use std::{i32, i64, u32, u8};
use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{FromIterator, IntoIterator, Iterator, repeat, once};
use std::mem::swap;
use std::rc::Rc;

// 水题，不过边角的 corner case 比较蛋疼。
impl Solution {
    pub fn candy(ratings: Vec<i32>) -> i32 {
        let n = ratings.len();
        if n == 0 {
            return 0;
        }
        let mut candies = vec![1; n];

        let mut i = 0;
        while i < n - 1 {
            let mut j = i;
            while j + 1 < n && ratings[j + 1] <= ratings[j] {
                j += 1;
            }
            let mut cand = 1;
            candies[j] = cand;
            for k in (i..j).rev() {
                if ratings[k] > ratings[k + 1] {
                    cand += 1;
                } else {
                    cand = 1;
                }
                if k == i {
                    candies[i] = max(candies[i], cand);
                } else {
                    candies[k] = cand;
                }
            }

            i = j;
            while i + 1 < n && ratings[i + 1] >= ratings[i] {
                i += 1;
            }
            cand = 1;
            for k in j + 1..=i {
                if ratings[k] > ratings[k - 1] {
                    cand += 1;
                } else {
                    cand = 1;
                }
                candies[k] = cand;
            }
        }
        //println!("candies = {:?}", candies);
        return candies.iter().sum();
    }
}
