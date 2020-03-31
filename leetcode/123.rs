use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{repeat, FromIterator, IntoIterator, Iterator};
use std::mem::swap;
use std::ptr::{null, null_mut};
use std::rc::Rc;
use std::{i32, i64, u32, u8};

impl Solution {
    // 买或不买，DP。
    pub fn wtf(prices: &Vec<i32>, profits: &mut Vec<i32>) -> i32 {
        let n = prices.len();
        let mut buy = vec![0; n];
        let mut maxP = i32::MIN;
        for i in 0..n {
            maxP = max(maxP, profits[i]);
            buy[i] = maxP - prices[i];
        }
        maxP = i32::MIN;
        for i in 0..n {
            maxP = max(maxP, buy[i]);
            profits[i] = maxP + prices[i];
        }
        return maxP;
    }

    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let n = prices.len();
        if n <= 1 {
            return 0;
        }

        let mut profits = vec![0; n];
        Self::wtf(&prices, &mut profits);
        Self::wtf(&prices, &mut profits); // 可进行几次，就 DP 几次。

        let mut maxP = i32::MIN;
        for i in 0..n {
            maxP = max(maxP, profits[i]);
        }
        return maxP;
    }
}
