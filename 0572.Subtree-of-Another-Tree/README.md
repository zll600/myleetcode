# [572. Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/)

## 题目

Given the roots of two binary trees `root` and `subRoot`, return `true` if there is a subtree of `root` with the same structure and node values of` subRoot` and `false` otherwise.

A subtree of a binary tree `tree` is a tree that consists of a node in `tree` and all of this node's descendants. The tree `tree` could also be considered as a subtree of itself.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/28/subtree1-tree.jpg)

```
Input: root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/28/subtree2-tree.jpg)

```
Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false
```

 

**Constraints:**

- The number of nodes in the `root` tree is in the range `[1, 2000]`.
- The number of nodes in the `subRoot` tree is in the range `[1, 1000]`.
- `-104 <= root.val <= 104`
- `-104 <= subRoot.val <= 104`

## 题目大意

给定两个二叉树的节点 root和subroot，如果 root 的一棵子树和 subroot 具有相同的结构则返回 true，否则返回 false，

s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。

## 解题思路

这道题目可以参考第 100 题，比较两颗树具有相同的结构，

### Solution 1

这种解法的基本就是利用 第 100 题的解法，对 root 的每个节点，与 subroot 进行匹配，

* 从当前节点开始匹配
* 在左子树中匹配
* 在右子树中匹配

`````c++
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
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        // 匹配当前节点
        if (IsSameTree(s, t)) {
            return true;
        }
        // 如果 root 为空，则直接返回 false
        if (!s) {
            return false;
        }
        
        // 匹配其左子树\右子树
        if (isSubtree(s->left, t) || isSubtree(s->right, t)) {
            return true;
        }
        
        return false;
    }
    
 private:
    // 判断两棵树的结构是否一样
    bool IsSameTree(TreeNode *s, TreeNode *t) {
        if (!s && !t) {  // 两者都空
            return true;
        }
        
        if (!s || !t) {  // 至少一个不为空
            return false;
        }
        
        return s->val == t->val  // 比较值
            && IsSameTree(s->left, t->left)  // 比较左子树
            && IsSameTree(s->right, t->right);  // 比较右子树
    }
};
`````

