impl Solution {
    pub fn min_moves2(mut nums: Vec<i32>) -> i32 {
        nums.sort();
        let n = nums.len();
        let (mut i, mut j) = (0, n - 1);
        let mut rv = 0;
        while i < j {
            rv += nums[j] - nums[i];
            i += 1;
            j -= 1;
        }
        return rv;
    }
}
