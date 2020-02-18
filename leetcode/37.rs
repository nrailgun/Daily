const N: usize = 9;
const SQRT_N: usize = 3;

impl Solution {
    fn conv(_b: &Vec<Vec<char>>) -> Vec<Vec<i8>> {
        let mut b = vec![vec![-1; N]; N];
        for i in 0..N {
            for j in 0..N {
                if _b[i][j] != '.' {
                    b[i][j] = (_b[i][j] as i32 - '1' as i32) as i8;
                }
            }
        }
        return b;
    }

    fn cons(b: &Vec<Vec<i8>>) -> (Vec<Vec<bool>>, Vec<Vec<bool>>, Vec<Vec<bool>>) {
        let (mut rc, mut cc, mut bc) = (
            vec![vec![false; N]; N], vec![vec![false; N]; N], vec![vec![false; N]; N],
        );
        for i in 0..N {
            for j in 0..N {
                let d = b[i][j];
                let k = i / SQRT_N * SQRT_N + j / SQRT_N;
                if d >= 0 {
                    rc[i][d as usize] = true;
                    cc[j][d as usize] = true;
                    bc[k][d as usize] = true;
                }
            }
        }
        return (rc, cc, bc);
    }

    fn solve(
        b: &mut Vec<Vec<i8>>, r: usize, c: usize,
        rc: &mut Vec<Vec<bool>>, cc: &mut Vec<Vec<bool>>, bc: &mut Vec<Vec<bool>>,
    ) -> bool {
        if r == N {
            return true;
        }
        let (nr, nc) = {
            if c == N - 1 {
                (r + 1, 0)
            } else {
                (r, c + 1)
            }
        };
        if b[r][c] >= 0 {
            return Self::solve(b, nr, nc, rc, cc, bc);
        }
        let k = r / SQRT_N * SQRT_N + c / SQRT_N;
        for i in 0..N {
            if rc[r][i] || cc[c][i] || bc[k][i] {
                continue;
            }
            b[r][c] = i as i8;
            rc[r][i] = true;
            cc[c][i] = true;
            bc[k][i] = true;
            if Self::solve(b, nr, nc, rc, cc, bc) {
                return true;
            }
            rc[r][i] = false;
            cc[c][i] = false;
            bc[k][i] = false;
        }
        b[r][c] = -1;
        return false;
    }

    pub fn solve_sudoku(_b: &mut Vec<Vec<char>>) {
        let mut b = Self::conv(_b);
        let (mut rc, mut cc, mut bc) = Self::cons(&b);
        let v = Self::solve(&mut b, 0, 0, &mut rc, &mut cc, &mut bc);
        if v {
            for i in 0..N {
                for j in 0..N {
                    _b[i][j] = (b[i][j] as u8 + '1' as u8) as char;
                }
            }
        }
    }
}
