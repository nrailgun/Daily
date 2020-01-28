impl Solution {
    pub fn query_string(s: String, n: i32) -> bool {
        for i in 1..(n + 1) {
            let is = format!("{:b}", i);
            if !s.contains(&is) {
                return false;
            }
        }
        return true;
    }
}
