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
    fn make_row(n: usize, c: usize) -> String {
        (0..n).map(|i| if i == c { 'Q' } else { '.' }).collect()
    }

    fn solve(sp: &mut Space, r: usize, o: &mut Vec<String>, os: &mut Vec<Vec<String>>) {
        let n = sp.n;
        for c in 0..n {
            let (ldi, cdi) = (sp.ldi(r, c), sp.cdi(r, c));
            if !sp.c[c] || !sp.ld[ldi] || !sp.cd[cdi] {
                continue;
            }
            sp.c[c] = false;
            sp.ld[ldi] = false;
            sp.cd[cdi] = false;
            let rstr = Self::make_row(n, c);
            o.push(rstr);
            if r + 1 == n {
                os.push(o.clone());
            } else {
                Self::solve(sp, r + 1, o, os);
            }
            o.pop();
            sp.c[c] = true;
            sp.ld[ldi] = true;
            sp.cd[cdi] = true;
        }
    }

    pub fn solve_n_queens(n: i32) -> Vec<Vec<String>> {
        let mut sp = Space::new(n as usize);
        let mut o = vec![];
        let mut os = vec![];
        Self::solve(&mut sp, 0, &mut o, &mut os);
        return os;
    }
}
