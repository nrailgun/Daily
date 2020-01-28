use std::cell::{BorrowMutError, Cell, RefCell};
use std::cmp::{max, min, Ordering};
use std::rc::Rc;
use std::sync::{Arc, Mutex};

impl Solution {
    pub fn distance_between_bus_stops(dists: Vec<i32>, start: i32, destination: i32) -> i32 {
        let mut sum = 0;
        let mut sums = vec![0];
        dists.iter().for_each(|x| {
            sum += x;
            sums.push(sum);
        });

        let a = min(start, destination) as usize;
        let b = max(start, destination) as usize;
        let d = sums[b] - sums[a];
        return min(d, sum - d);
    }
}
