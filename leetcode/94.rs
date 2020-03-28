impl Solution {
    fn wtf(root: Option<Rc<RefCell<TreeNode>>>, o: &mut Vec<i32>) {
        match root {
            None => {}
            Some(rc) => {
                let a: Ref<TreeNode> = rc.borrow();
                Self::wtf(a.left.clone(), o);
                o.push(a.val);
                Self::wtf(a.right.clone(), o);
            }
        };
    }

    pub fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
        let mut o = vec![];
        Self::wtf(root, &mut o);
        return o;
    }
}
