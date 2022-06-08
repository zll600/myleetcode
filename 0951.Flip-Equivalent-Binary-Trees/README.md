# [951. Flip Equivalent Binary Trees](https://leetcode.cn/problems/flip-equivalent-binary-trees/)

## 题目

For a binary tree **T**, we can define a **flip operation** as follows: choose any node, and swap the left and right child subtrees.

A binary tree **X** is *flip equivalent* to a binary tree **Y** if and only if we can make **X** equal to **Y** after some number of flip operations.

Given the roots of two binary trees `root1` and `root2`, return `true` if the two trees are flip equivalent or `false` otherwise.

 

**Example 1:**

![Flipped Trees Diagram](https://assets.leetcode.com/uploads/2018/11/29/tree_ex.png)

```
Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 = [1,3,2,null,6,4,5,null,null,null,null,8,7]
Output: true
Explanation: We flipped at nodes with values 1, 3, and 5.
```

**Example 2:**

```
Input: root1 = [], root2 = []
Output: true
```

**Example 3:**

```
Input: root1 = [], root2 = [1]
Output: false
```

 

**Constraints:**

- The number of nodes in each tree is in the range `[0, 100]`.
- Each tree will have **unique node values** in the range `[0, 99]`.

## 题目大意

我们可以为二叉树 T 定义一个 翻转操作 ，如下所示：选择任意节点，然后交换它的左子树和右子树。

只要经过一定次数的翻转操作后，能使 X 等于 Y，我们就称二叉树 X 翻转 等价 于二叉树 Y。

这些树由根节点 root1 和 root2 给出。如果两个二叉树是否是翻转 等价 的函数，则返回 true ，否则返回 false

## 解题思路

这道题目很想二叉树的镜像那道题目

### Solution 1:

这种解法利用二叉树的前序遍历来做判断

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
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) {
            return true;
        } else if (!root1 || !root2) {
            return false;
        } else if (root1->val != root2->val) {
            return false;
        }
        
        return (flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right))
            || (flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left));

    }
};
````
