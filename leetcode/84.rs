impl Solution {
    // 一个 $h$ 对应最大的 rect，肯定是两端走第一个比 h 低的矩形为止。
    // 所以先找到两端比 $h$ 小的 $h'$ 的位置，利用 stack 在 $O(1)$ 时间找到（$O(n)$ 时间预处理建 stack）。
    pub fn largest_rectangle_area(hs: Vec<i32>) -> i32 {
        let mut bis = vec![];
        let mut st: Vec<(usize, i32)> = vec![];
        for (i, h) in hs.iter().enumerate() {
            loop {
                if st.is_empty() {
                    st.push((i, *h));
                    bis.push(None);
                    break;
                } else {
                    let last: (usize, i32) = st.last().unwrap().clone();
                    if last.1 < *h {
                        st.push((i, *h));
                        bis.push(Some(last.0));
                        break;
                    } else {
                        st.pop();
                    }
                }
            }
        }

        let mut fis = vec![];
        let mut st: Vec<(usize, i32)> = vec![];
        for (i, h) in hs.iter().enumerate().rev() {
            loop {
                if st.is_empty() {
                    st.push((i, *h));
                    fis.push(None);
                    break;
                } else {
                    let last: (usize, i32) = st.last().unwrap().clone();
                    if last.1 < *h {
                        st.push((i, *h));
                        fis.push(Some(last.0));
                        break;
                    } else {
                        st.pop();
                    }
                }
            }
        }
        fis.reverse();

        let n = hs.len();
        let mut max_area = 0;
        for (i, h) in hs.iter().enumerate() {
            let l = 1 +
                match bis[i] {
                    None => i,
                    Some(bi) => i - bi - 1,
                }
                +
                match fis[i] {
                    None => n - 1 - i,
                    Some(fi) => fi - 1 - i,
                };
            let area = l as i32 * *h;
            max_area = max(max_area, area);
        }
        return max_area;
    }
}
