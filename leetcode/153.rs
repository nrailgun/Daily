impl Solution {
    pub fn find_min(a: Vec<i32>) -> i32 {
        if a.len() <= 1 {
            return a[0];
        }

        let (mut lb, mut ub) = (0, a.len() - 1);
        while lb < ub {
            let mid = (lb + ub) / 2;
            if a[mid] > a[ub] {
                lb = mid + 1;
            } else if a[mid] < a[ub] {
                ub = mid;
            }
        }
        return a[lb];
    }
}
