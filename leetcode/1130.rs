use std::cell::{BorrowMutError, Cell, RefCell};
use std::cmp::{max, min, Ordering};
use std::i32;
use std::rc::Rc;
use std::sync::{Arc, Mutex};

impl Solution {
    fn make_rmq(a: &Vec<i32>) -> Vec<Vec<i32>> {
        let n = a.len();
        let mut dp = vec![vec![i32::MIN; n]; n];
        for i in 0..n {
            let mut mv = i32::MIN;
            for j in i..n {
                mv = max(mv, a[j]);
                dp[i][j] = mv;
            }
        }
        return dp;
    }

    pub fn mct_from_leaf_values(a: Vec<i32>) -> i32 {
        let rmq = Self::make_rmq(&a);
        let n = a.len();
        let mut dp = vec![vec![i32::MIN; n]; n];

        for i in (0..n).rev() {
            dp[i][i] = 0;
            for j in (i + 1)..n {
                let mut mv = i32::MAX;
                for k in i..j {
                    //println!("i={}, k={}, j={}", i, k, j);
                    //println!("a={}, b={}, c={}, d={}", dp[i][k], dp[k + 1][j], rmq[i][k], rmq[k + 1][j]);
                    let newv = dp[i][k] + dp[k + 1][j] + rmq[i][k] * rmq[k + 1][j];
                    mv = min(mv, newv);
                }
                dp[i][j] = mv;
            }
        }
        return dp[0][n - 1];
    }
}
