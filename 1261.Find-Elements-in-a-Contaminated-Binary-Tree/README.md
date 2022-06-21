#### [1261. Find Elements in a Contaminated Binary Tree](https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/)

Given a binary tree with the following rules:

1. `root.val == 0`
2. If `treeNode.val == x` and `treeNode.left != null`, then `treeNode.left.val == 2 * x + 1`
3. If `treeNode.val == x` and `treeNode.right != null`, then `treeNode.right.val == 2 * x + 2`

Now the binary tree is contaminated, which means all `treeNode.val` have been changed to `-1`.

Implement the `FindElements` class:

- `FindElements(TreeNode* root)` Initializes the object with a contaminated binary tree and recovers it.
- `bool find(int target)` Returns `true` if the `target` value exists in the recovered binary tree.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/11/06/untitled-diagram-4-1.jpg)

```
Input
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
Output
[null,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1]); 
findElements.find(1); // return False 
findElements.find(2); // return True 
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/11/06/untitled-diagram-4.jpg)

```
Input
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
Output
[null,true,true,false]
Explanation
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/11/07/untitled-diagram-4-1-1.jpg)

```
Input
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
Output
[null,true,false,false,true]
Explanation
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True
```

 

**Constraints:**

- `TreeNode.val == -1`
- The height of the binary tree is less than or equal to `20`
- The total number of nodes is between `[1, 104]`
- Total calls of `find()` is between `[1, 104]`
- `0 <= target <= 106`



给出一个满足下述规则的二叉树：

    root.val == 0
    如果 treeNode.val == x 且 treeNode.left != null，那么 treeNode.left.val == 2 * x + 1
    如果 treeNode.val == x 且 treeNode.right != null，那么 treeNode.right.val == 2 * x + 2

现在这个二叉树受到「污染」，所有的 treeNode.val 都变成了 -1。

请你先还原二叉树，然后实现 FindElements 类：

    FindElements(TreeNode* root) 用受污染的二叉树初始化对象，你需要先把它还原。
    bool find(int target) 判断目标值 target 是否存在于还原后的二叉树中并返回结果。



## 解题思路

这道题目还可以看看 [这个思路](https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/solution/bu-yong-setde-findfang-fa-by-cyanflxy/)

### Solution 1:

这里使用二叉树的前序遍历来构造树，同时在构造树的同时可以可以使用 set 来缓存构造中的每个节点的值，可以加速 find 查找

````c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class FindElements {
public:
    FindElements(TreeNode* root) {
        if (!root) {
            return;
        }
        root->val = 0;
        data_.insert(0);
        DFS(root);
    }
    
    bool find(int target) {
        return data_.find(target) != data_.end();
    }
    
 private:
    set<int> data_;
 
    void DFS(TreeNode *root) {
        if (root->left != nullptr) {
            root->left->val = root->val * 2 + 1;
            data_.insert(root->left->val);
            DFS(root->left);
        }
        if (root->right != nullptr) {
            root->right->val = root->val * 2 + 2;
            data_.insert(root->right->val);
            DFS(root->right);
        }
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
````

