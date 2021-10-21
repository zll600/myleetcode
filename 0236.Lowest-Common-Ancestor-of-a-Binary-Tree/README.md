# [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

## 题目

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes `p` and `q` as the lowest node in `T` that has both `p` and `q` as descendants (where we allow **a node to be a descendant of itself**).”

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/12/14/binarytree.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
```

**Example 3:**

```
Input: root = [1,2], p = 1, q = 2
Output: 1
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[2, 105]`.
- `-109 <= Node.val <= 109`
- All `Node.val` are **unique**.
- `p != q`
- `p` and `q` will exist in the tree.

## 题目大意

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

## 解题思路

这道题目和第 236 题很像，

具体方法就是在左右子树中分别去找

* 如果在左子树和右子树中都找到了，直接返回当前节点，就是最终结果
* 如果在左子树未找到，而在右子树中找到，返回找到的节点，表示在当前部分找到了
* 如果在右子树中未找到，而在左子树中找到，返回找到的节点，表示在当前部分找到了
* 后两种情况会一直向上传递，直到在一个节点的左子树和右子树中都找到

`````c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 为空
        // 或者找到二者其中之一
        if (!root || root == p || root == q) {
            return root;
        }

        // 到左子树中找
        TreeNode *left_node = lowestCommonAncestor(root->left, p, q);
        // 到右子树中找
        TreeNode *right_node = lowestCommonAncestor(root->right, p, q);

        // 左子树中没有找到
        if (!left_node) {
            return right_node;
        }
        // 右子树中没有找到
        if (!right_node) {
            return left_node;
        }

        return root;
    }
};
`````

