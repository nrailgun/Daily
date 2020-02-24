use std::mem::swap;

impl Solution {
    fn map(i: usize, j: usize, n: usize) -> (usize, usize) {
        (j, n - 1 - i)
    }

    pub fn rotate(mat: &mut Vec<Vec<i32>>) {
        let n = mat.len();
        'o: for i in 0..(n / 2) {
            for j in i..(n - i - 1) {
                let (mut ni, mut nj) = (i, j);
                let mut v = mat[i][j];
                loop {
                    let (_ni, _nj) = Self::map(ni, nj, n);
                    ni = _ni;
                    nj = _nj;
                    swap(&mut mat[ni][nj], &mut v);
                    if ni == i && nj == j {
                        break;
                    }
                }
            }
        }
    }
}
