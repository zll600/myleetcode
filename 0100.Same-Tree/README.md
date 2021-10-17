# [100. Same Tree](https://leetcode.com/problems/same-tree/)

## 题目

Given the roots of two binary trees `p` and `q`, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/12/20/ex1.jpg)

```
Input: p = [1,2,3], q = [1,2,3]
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/12/20/ex2.jpg)

```
Input: p = [1,2], q = [1,null,2]
Output: false
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2020/12/20/ex3.jpg)

```
Input: p = [1,2,1], q = [1,1,2]
Output: false
```

 

**Constraints:**

- The number of nodes in both trees is in the range `[0, 100]`.
- `-104 <= Node.val <= 104`

## 题目大意

给定两个二叉树的根节点，编写一个函数检验它们是否是一样的，

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。

## 解题思路

这道题的核心就是同时按照相同的顺序遍历两棵树，如果任意一个节点出现不匹配的情况，就返回 false，全部匹配返回 true

### Solution1: Recursive

这中递归解法，同时对两棵树进行前序遍历，一旦不匹配直接退出循环

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
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 如果二者都为空
        if (p == nullptr && q == nullptr) {
            return true;
        }
        // 如果 p 为空
        if (p == nullptr) {
            return false;
        }
        // 如果 q 为空
        if (q == nullptr) {
            return false;
        }
        
        /*
        if (!p || !q) {
        	return false;
        }
        */
        
        // 检验当前节点的值
        // 以及左子树和右子树
        return p->val == q->val && isSameTree(p->left, q->left)
            && isSameTree(p->right, q->right);
    }
};
````