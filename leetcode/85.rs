use std::{i32, i64, u32, u8};
use std::cell::{BorrowMutError, Cell, Ref, RefCell, RefMut};
use std::cmp::{max, min, Ordering};
use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet, VecDeque};
use std::iter::{FromIterator, IntoIterator, Iterator, repeat};
use std::mem::swap;
use std::rc::Rc;

impl Solution {
    fn calc_h(mat: &Vec<Vec<char>>) -> Vec<Vec<i32>> {
        let (m, n) = (mat.len(), mat[0].len());
        let mut h = vec![vec![0; n]; m];
        for i in 0..n {
            for j in (0..m).rev() {
                if mat[j][i] == '0' {
                    h[j][i] = 0;
                } else {
                    h[j][i] = if j + 1 == m { 1 } else { h[j + 1][i] + 1 };
                }
            }
        }
        return h;
    }

    // O(N)
    fn row_max_area(hs: &Vec<i32>) -> i32 {
        let n = hs.len();

        let mut st: Vec<(usize, i32)> = vec![];
        let mut lh: Vec<Option<usize>> = vec![];
        for (i, h) in hs.iter().enumerate() {
            loop {
                if st.is_empty() {
                    st.push((i, *h));
                    lh.push(None);
                    break;
                } else {
                    let last: (usize, i32) = st.last().unwrap().clone();
                    if last.1 < *h {
                        st.push((i, *h));
                        lh.push(Some(last.0));
                        break;
                    } else {
                        st.pop();
                    }
                }
            }
        }

        st = vec![];
        let mut rh: Vec<Option<usize>> = vec![];
        for (i, h) in hs.iter().enumerate().rev() {
            loop {
                if st.is_empty() {
                    st.push((i, *h));
                    rh.push(None);
                    break;
                } else {
                    let last: (usize, i32) = st.last().unwrap().clone();
                    if last.1 < *h {
                        st.push((i, *h));
                        rh.push(Some(last.0));
                        break;
                    } else {
                        st.pop();
                    }
                }
            }
        }
        rh.reverse();

        let mut maxa = 0;
        for (i, h) in hs.iter().enumerate() {
            let l = 1
                +
                match lh[i] {
                    None => i,
                    Some(j) => i - j - 1,
                }
                +
                match rh[i] {
                    None => n - 1 - i,
                    Some(j) => j - i - 1,
                };
            let a = l as i32 * *h;
            maxa = max(maxa, a);
        }
        return maxa;
    }

    // O(MN)
    // 把每一行的情况都当做“柱状图最大矩形面积”处理。
    pub fn maximal_rectangle(mat: Vec<Vec<char>>) -> i32 {
        let m = mat.len();
        if m == 0 {
            return 0;
        }
        let n = mat[0].len();
        let hm = Self::calc_h(&mat);

        let mut maxa = 0;
        for i in 0..m {
            let a = Self::row_max_area(&hm[i]);
            maxa = max(maxa, a);
        }
        return maxa;
    }

    // O(MN^2)
    pub fn maximal_rectangle_1(mat: Vec<Vec<char>>) -> i32 {
        let m = mat.len();
        if m == 0 {
            return 0;
        }
        let n = mat[0].len();

        let h = Self::calc_h(&mat);
        let mut maxa: i32 = 0;
        for i in 0..m {
            for j in 0..n {
                let mut minh = i32::MAX;
                for k in j..n {
                    minh = min(minh, h[i][k]);
                    let a = (k - j + 1) as i32 * minh;
                    maxa = max(maxa, a);
                }
            }
        }
        return maxa;
    }
}
