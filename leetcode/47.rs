// 这是一个错误解，为什么呢？
impl Solution {
    fn _permute(s: &mut [i32]) -> Vec<Vec<i32>> {
        let sl = s.len();
        if sl == 1 {
            return vec![vec![s[0]]];
        }

        let mut ps: Vec<Vec<i32>> = vec![];
        let mut i = 0;
        while i < sl {
            s.swap(0, i);
            // `_permute` 的 pre cond 就是 `s` 有序，在这个过程中，有序性质被破坏了。如果要继续保持有序，需
            // 要重新排序，代价比较大。
            // 一种思路是用链表来记录，比较容易随意删除元素，插入元素（rust 的 linked list 比较僵硬）。
            // 另一种更灵活一点的思路是使用一个数组来记录每个位置上的元素是不是被用掉了，而不需要另外建立 list。
            let mut _ps = Self::_permute(&mut s[1..]);
            for mut _p in _ps.into_iter() {
                _p.push(s[0]);
                ps.push(_p);
            }
            s.swap(0, i);

            let j = i;
            while i < sl && s[i] == s[j] {
                i += 1;
            }
        }
        return ps;
    }

    pub fn permute_unique(mut a: Vec<i32>) -> Vec<Vec<i32>> {
        a.sort();
        Self::_permute(&mut a[..])
    }
}


impl Solution {
    fn _permute(s: &Vec<i32>, used: &mut Vec<bool>, d: usize) -> Vec<Vec<i32>> {
        let sl = s.len();
        let mut ps: Vec<Vec<_>> = vec![];
        let mut i = 0;
        while i < sl {
            if used[i] {
                i += 1;
            } else {
                if sl == d + 1 {
                    return vec![vec![s[i]]];
                } else {
                    used[i] = true;
                    let mut _ps = Self::_permute(s, used, d + 1);
                    for mut _p in _ps.into_iter() {
                        _p.push(s[i]);
                        ps.push(_p);
                    }
                    used[i] = false;
                }
                let j = i;
                while i < sl && s[i] == s[j] {
                    i += 1;
                }
            }
        }
        return ps;
    }

    pub fn permute_unique(mut a: Vec<i32>) -> Vec<Vec<i32>> {
        a.sort();
        let mut used = vec![false; a.len()];
        Self::_permute(&a, &mut used, 0)
    }
}
