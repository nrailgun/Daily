use std::cell::{BorrowMutError, Cell, RefCell};
use std::cmp::{max, min, Ordering};
use std::rc::Rc;
use std::sync::{Arc, Mutex};

impl Solution {
    pub fn min_insertions(s: String) -> i32 {
        let s = s.chars().collect::<Vec<_>>();
        let l = s.len();
        let mut dp = vec![vec![0; l]; l];

        for i in (0..l).rev() {
            for j in (i + 1)..l {
                if s[i] == s[j] {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = 1 + min(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][l - 1];
    }
}
