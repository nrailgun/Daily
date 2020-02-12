use std::cell::{BorrowMutError, Cell, Ref, RefMut, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::{i32, u32, i64, f32, f64};
use std::iter::{Iterator, FromIterator};
use std::mem::swap;
use std::rc::Rc;

impl Solution {
    fn lc(digits: &str) -> Vec<String> {
        let mut v = vec![];
        let oc = digits.chars().next();
        match oc {
            None => {
                v.push(String::new());
            },
            Some(c) => {
                let chs = {
                    match c {
                        '2' => vec!["a", "b", "c"],
                        '3' => vec!["d", "e", "f"],
                        '4' => vec!["g", "h", "i"],
                        '5' => vec!["j", "k", "l"],
                        '6' => vec!["m", "n", "o"],
                        '7' => vec!["p", "q", "r", "s"],
                        '8' => vec!["t", "u", "v"],
                        '9' => vec!["w", "x", "y", "z"],
                        _ => unreachable!(),
                    }
                };
                let _v = Self::lc(&digits[1..]);
                for c in chs {
                    for s in &_v {
                        let x = c.to_owned() + s;
                        v.push(x);
                    }
                }
            }
        }
        return v;
    }

    pub fn letter_combinations(digits: String) -> Vec<String> {
        if digits.len() == 0 {
            return vec![];
        }
        return Self::lc(&digits);
    }
}
