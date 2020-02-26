impl Solution {
    pub fn set_zeroes(mat: &mut Vec<Vec<i32>>) {
        let m = mat.len();
        if m == 0 {
            return;
        }
        let n = mat[0].len();
        if n == 0 {
            return;
        }

        let mut zrow = None;
        'l: for i in 0..m {
            for j in 0..n {
                if mat[i][j] == 0 {
                    zrow = Some(i);
                    break 'l;
                }
            }
        }
        if zrow.is_none() {
            return;
        }
        let zrow: usize = zrow.unwrap();

        for i in 0..m {
            if i == zrow {
                continue;
            }
            let mut z = false;
            for j in 0..n {
                if mat[i][j] == 0 {
                    z = true;
                    mat[zrow][j] = 0;
                }
            }
            if z {
                for j in 0..n {
                    mat[i][j] = 0;
                }
            }
        }

        for j in 0..n {
            if mat[zrow][j] != 0 {
                mat[zrow][j] = 0;
            } else {
                for i in 0..m {
                    mat[i][j] = 0;
                }
            }
        }
    }
}
