impl Solution {
    pub fn num_jewels_in_stones(j: String, s: String) -> i32 {
        let mut zvec: Vec<bool> = vec![false; 256];
        for c in j.chars() {
            let i = c as usize - 0;
            zvec[i] = true;
        }

        let mut cnt = 0;
        for c in s.chars() {
            let i = c as usize - 0;
            if zvec[i] {
                cnt += 1;
            }
        }
        return cnt;
    }
}
