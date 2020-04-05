// 和买股票题是一样的。
impl Solution {
    pub fn can_complete_circuit(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
        let n = gas.len();
        let mut i = 0;
        let mut i_step = 0;
        while i_step < n {
            let mut j = i;
            let mut left = gas[i] - cost[i];
            let mut j_step = 0;
            while left >= 0 {
                j = (j + 1) % n;
                left += gas[j] - cost[j];
                j_step += 1;
                if j_step == n {
                    return i as i32;
                }
            }
            i = (j + 1) % n;
            i_step += j_step + 1;
        }
        return -1;
    }
}
