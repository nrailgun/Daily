impl Solution {
    pub fn sort_colors(a: &mut Vec<i32>) {
        let n = a.len();
        let (mut i, mut i0, mut i2) = (0, 0, n - 1);
        while i < n {
            match a[i] {
                0 => {
                    a.swap(i, i0);
                    i0 += 1;
                    if a[i] == 0 {
                        i += 1;
                    }
                }
                1 => {
                    i += 1;
                }
                2 => {
                    while i2 > i && a[i2] == 2 {
                        i2 -= 1;
                    }
                    if i2 > i {
                        a.swap(i, i2);
                        i2 -= 1;
                    } else {
                        break;
                    }
                }
                _ => {
                    unreachable!();
                }
            }
        }
    }
}
