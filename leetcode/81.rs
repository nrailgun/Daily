impl Solution {
    pub fn linear(a: &[i32], tg: i32) -> bool {
        for i in 0..a.len() {
            if a[i] == tg {
                return true;
            }
        }
        return false;
    }

    // `a` contains duplicates
    pub fn search(a: Vec<i32>, tg: i32) -> bool {
        let n = a.len();
        if n == 0 {
            return false;
        }

        let (mut lb, mut ub) = (0, n - 1);
        loop {
            if ub - lb < 2 {
                return Self::linear(&a[lb..=ub], tg);
            }

            let mid = (lb + ub) / 2;
            if a[mid] == tg {
                return true;
            }

            if a[lb] == a[ub] {
                lb += 1;
            } else if a[lb] < a[ub] {
                if a[mid] < tg {
                    lb = mid + 1;
                } else {
                    ub = mid;
                }
            } else {
                if a[lb] == a[mid] {
                    lb += 1;
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
}
