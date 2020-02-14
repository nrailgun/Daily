impl Solution {
    pub fn linear(a: &[i32], tg: i32, lb: usize) -> i32 {
        for i in 0..a.len() {
            if a[i] == tg {
                return (lb + i) as i32;
            }
        }
        return -1;
    }

    // assuming no duplicate
    pub fn search(a: Vec<i32>, tg: i32) -> i32 {
        let n = a.len();
        if n == 0 {
            return -1;
        }

        let (mut lb, mut ub) = (0, n - 1);
        loop {
            if ub - lb < 2 {
                return Self::linear(&a[lb..ub + 1], tg, lb);
            }

            let mid = (lb + ub) / 2;
            if a[mid] == tg {
                return mid as i32;
            }
            if a[lb] < a[ub] {
                if a[mid] < tg {
                    lb = mid + 1;
                } else {
                    ub = mid;
                }
            } else if a[lb] < a[mid] {
                if a[lb] <= tg && tg < a[mid] {
                    ub = mid;
                } else {
                    lb = mid + 1;
                }
            } else {
                if a[mid] < tg && tg <= a[ub] {
                    lb = mid + 1;
                } else {
                    ub = mid;
                }
            }
        }
    }
}
