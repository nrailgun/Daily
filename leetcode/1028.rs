impl Solution {
    fn leadings(s: &str) -> (usize, &str) {
        let mut d = 0;
        loop {
            let o = s.chars().nth(d);
            if o.is_none() || o.unwrap() != '-' {
                break;
            }
            d += 1;
        }
        return (d, &s[d..]);
    }

    fn number(s: &str) -> (usize, &str, i32) {
        let mut d = 0;
        loop {
            let o = s.chars().nth(d);
            if o.is_none() || !o.unwrap().is_digit(10) {
                break;
            }
            d += 1;
        }
        let v = *(&s[..d].parse::<i32>().unwrap());
        return (d, &s[d..], v);
    }

    fn solve(s: &str) -> (&str, Option<Rc<RefCell<TreeNode>>>) {
        if s == "" {
            return (s, None);
        }

        let (d1, s1) = Self::leadings(s);
        let (_, s2, v) = Self::number(s1);
        let mut root = TreeNode { val: v, left: None, right: None };

        let (d2, _) = Self::leadings(s2);
        if d2 <= d1 {
            return (s2, Some(Rc::new(RefCell::new(root))));
        }
        let (s3, lroot) = Self::solve(s2);
        root.left = lroot;

        let (d3, _) = Self::leadings(s3);
        if d3 <= d1 {
            return (s3, Some(Rc::new(RefCell::new(root))));
        }
        let (s4, rroot) = Self::solve(s3);
        root.right = rroot;

        return (s4, Some(Rc::new(RefCell::new(root))));
    }

    pub fn recover_from_preorder(s: String) -> Option<Rc<RefCell<TreeNode>>> {
        let (_, root) = Self::solve(&s);
        return root;
    }
}
