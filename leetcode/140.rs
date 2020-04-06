impl Solution {
    fn gen(ws: &Vec<String>, dp: &Vec<Vec<usize>>, i: usize, s: &mut String, ss: &mut Vec<String>) {
        if i == dp.len() {
            ss.push(s.clone());
        } else {
            let slen = s.len();
            for &wi in &dp[i] {
                if i != 0 {
                    s.push_str(" ");
                }
                s.push_str(&ws[wi]);
                Self::gen(ws, dp, i + ws[wi].len(), s, ss);
                s.truncate(slen);
            }
        }
    }

    pub fn word_break(s: String, ws: Vec<String>) -> Vec<String> {
        let n = s.len();
        assert!(n > 0);

        // 这道题其实是水题，做法就是非常简单的记忆化暴力搜索。
        let mut dp: Vec<Vec<usize>> = vec![vec![]; n];
        for i in (0..n).rev() {
            for (wi, w) in ws.iter().enumerate() {
                let wh = match (i + 1).checked_sub(w.len()) {
                    None => { continue; }
                    Some(x) => x,
                };
                if i + 1 < n && dp[i + 1].is_empty() {
                    continue;
                };
                if s[wh..=i].eq(w) {
                    dp[wh].push(wi);
                }
            }
        }

        // 而然，不能直接记忆存储字符串，否则会**像 LeetCode 题解一样超时**，只能记忆索引，最后
        // 再恢复出来。
        let mut s = String::new();
        let mut ss = vec![];
        Self::gen(&ws, &dp, 0, &mut s, &mut ss);
        return ss;
    }
}
