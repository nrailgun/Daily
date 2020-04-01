use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{repeat, FromIterator, IntoIterator, Iterator};
use std::mem::swap;
use std::ptr::{null, null_mut};
use std::rc::Rc;
use std::{i32, i64, u32, u8};

impl Solution {
    // DP 是 `isPalindrome()` 的高速实现。
    fn genIsPalindrome(s: &Vec<char>) -> Vec<Vec<bool>> {
        let n = s.len();
        let mut dp = vec![vec![false; n]; n];
        for i in (0..n).rev() {
            for j in i..n {
                dp[i][j] = {
                    if i + 1 >= j {
                        s[i] == s[j]
                    } else {
                        s[i] == s[j] && dp[i + 1][j - 1]
                    }
                };
            }
        }
        return dp;
    }

    // 思路很 naive 的暴力回溯，参考答案也是这个思路。但是实现不好，速度很慢。
    fn bt(
        isP: &Vec<Vec<bool>>,
        cache: &mut Vec<Vec<Option<Vec<Vec<String>>>>>,
        s: &Vec<char>,
        beg: usize,
        end: usize,
        expand: bool,
    ) -> Vec<Vec<String>> {
        let mut aa: Vec<Vec<String>>;
        if !expand {
            aa = vec![];
        } else {
            if let Some(ref _aa) = cache[beg][end] {
                aa = _aa.clone();
            } else {
                aa = vec![];
                for i in beg..end {
                    let aa1 = Self::bt(isP, cache, s, beg, i, false);
                    let aa2 = Self::bt(isP, cache, s, i + 1, end, true);
                    for a1 in &aa1 {
                        for a2 in &aa2 {
                            let a3: Vec<String> =
                                a1.iter().chain(a2.iter()).map(String::clone).collect();
                            aa.push(a3);
                        }
                    }
                }
                cache[beg][end] = Some(aa.clone());
            }
        }
        if isP[beg][end] {
            let x = s[beg..=end].iter().collect::<String>();
            aa.push(vec![x]);
        }
        return aa;
    }

    pub fn partition(s: String) -> Vec<Vec<String>> {
        let c: Vec<_> = s.chars().collect();
        let n = c.len();
        if n == 0 {
            return vec![];
        }
        let isP = Self::genIsPalindrome(&c);
        return Self::bt(&isP, &mut vec![vec![None; n]; n], &c, 0, n - 1, true);
    }
}
