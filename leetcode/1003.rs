use std::borrow::Borrow;
use std::cell::{BorrowMutError, Cell, RefCell};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet};
use std::i32;
use std::iter::{Iterator, FromIterator};
use std::ops::Deref;
use std::rc::Rc;
use std::sync::{Arc, Mutex};

impl Solution {
    pub fn is_valid(s: String) -> bool {
        let mut st = Vec::<i32>::new();
        for c in s.chars() {
            let n = st.len();
            match c {
                'a' => {
                    st.push(1);
                }
                'b' => {
                    if n < 1 || st[n - 1] != 1 {
                        return false;
                    }
                    st[n - 1] = 2;
                }
                'c' => {
                    if n < 1 || st[n - 1] != 2 {
                        return false;
                    }
                    st.pop();
                }
                _ => {
                    return false;
                }
            }
        }
        return st.is_empty();
    }
}
