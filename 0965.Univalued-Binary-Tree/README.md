# [965. Univalued Binary Tree](https://leetcode.com/problems/univalued-binary-tree/)

## 题目

A binary tree is **uni-valued** if every node in the tree has the same value.

Given the `root` of a binary tree, return `true` *if the given tree is **uni-valued**, or* `false` *otherwise.*

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/12/28/unival_bst_1.png)

```
Input: root = [1,1,1,1,1,null,1]
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/12/28/unival_bst_2.png)

```
Input: root = [2,2,2,5,2]
Output: false
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 100]`.
- `0 <= Node.val < 100`

## 题目大意

如果二叉树每个节点都具有相同的值，那么该二叉树就是*单值*二叉树。

只有给定的树是单值二叉树时，才返回 `true`；否则返回 `false`。

## 解题思路

这道题目很简单，按照题目要求来做即可

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
    bool isUnivalTree(TreeNode* root) {
        return IsUnivalTree(root, root->val);
    }
    
 private:
    bool IsUnivalTree(TreeNode *root, int target) {
        if (!root) {  // 如果为空，返回 true
            return true;
        }
        
        if (root->val != target) {  // 如果不为空但是值不相等，返回 false
            return false;
        }
        
        // 递归判断左右子树的是否符合条件
        return IsUnivalTree(root->left, target)
            && IsUnivalTree(root->right, target);
    }
};
`````

