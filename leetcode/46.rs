impl Solution {
    fn _permute(s: &mut [i32]) -> Vec<Vec<i32>> {
        let sl = s.len();
        if sl == 1 {
            return vec![vec![s[0]]];
        }

        let mut ps: Vec<Vec<i32>> = vec![];
        for i in 0..sl {
            s.swap(0, i);
            let mut _ps = Self::_permute(&mut s[1..]);
            for mut _p in _ps.into_iter() {
                _p.push(s[0]); // 其实放在后面也可以，题目没有要求顺序。
                ps.push(_p);
            }
            s.swap(0, i);
        }
        return ps;
    }

    pub fn permute(mut a: Vec<i32>) -> Vec<Vec<i32>> {
        Self::_permute(&mut a[..])
    }
}
