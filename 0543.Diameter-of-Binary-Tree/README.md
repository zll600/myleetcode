# [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

##  题目

Given the `root` of a binary tree, return *the length of the **diameter** of the tree*.

The **diameter** of a binary tree is the **length** of the longest path between any two nodes in a tree. This path may or may not pass through the `root`.

The **length** of a path between two nodes is represented by the number of edges between them.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/03/06/diamtree.jpg)

```
Input: root = [1,2,3,4,5]
Output: 3
Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
```

**Example 2:**

```
Input: root = [1,2]
Output: 1
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `-100 <= Node.val <= 100`

## 题目大意

给定一棵二叉树的根节点，返回二叉树直径的长度

二叉树的直径是指，两个节点之间路径的最长长度，这个路径不必非得经过根节点，

两结点之间的路径长度是以它们之间边的数目表示。

## 解题思路

### Solution1:

这种解法，采用后序遍历，求得左子树部分的最大距离，右子树部分的最大距离，然后用两者之后（表示经过当前节点的路径）更新结果，然后返回给上一次，这一层的最大值 + 1。

`````c++
/*
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
    int diameterOfBinaryTree(TreeNode* root) {
        DFS(root);
        return res_;
    }
 private:
    int res_;
    
    int DFS(TreeNode *root) {
        if (!root) {
            return 0;
        }
        
        // 先求左子树的高度
        int left_len = DFS(root->left);
        // 再求右子树的高度
        int right_len = DFS(root->right);
        // 更新最大值
        res_ = max(res_, left_len + right_len);
        // 返回结果
        return max(left_len, right_len) + 1;
    }
};
`````

