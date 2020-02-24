use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{HashMap, HashSet, VecDeque};
use std::iter::{FromIterator, Iterator, repeat};
use std::mem::swap;
use std::rc::Rc;
use std::{i32, i64, u32};

struct Space {
    n: usize,
    c: Vec<bool>,
    ld: Vec<bool>,
    cd: Vec<bool>,
}

impl Space {
    fn new(n: usize) -> Self {
        Self {
            n,
            c: vec![true; n],
            ld: vec![true; 2 * n - 1],
            cd: vec![true; 2 * n - 1],
        }
    }

    fn ldi(&self, r: usize, c: usize) -> usize {
        self.n - 1 + r - c
    }

    fn cdi(&self, r: usize, c: usize) -> usize {
        r + c
    }
}

impl Solution {
    fn solve(sp: &mut Space, r: usize) -> i32 {
        let n = sp.n;
        let mut cnt = 0;
        for c in 0..n {
            let (ldi, cdi) = (sp.ldi(r, c), sp.cdi(r, c));
            if !sp.c[c] || !sp.ld[ldi] || !sp.cd[cdi] {
                continue;
            }
            sp.c[c] = false;
            sp.ld[ldi] = false;
            sp.cd[cdi] = false;
            if r + 1 == n {
                cnt += 1;
            } else {
                cnt += Self::solve(sp, r + 1);
            }
            sp.c[c] = true;
            sp.ld[ldi] = true;
            sp.cd[cdi] = true;
        }
        return cnt;
    }

    pub fn total_n_queens(n: i32) -> i32 {
        let mut sp = Space::new(n as usize);
        Self::solve(&mut sp, 0)
    }
}
