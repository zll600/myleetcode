# [111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/)

## 题目

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

**Note:** A leaf is a node with no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/12/ex_depth.jpg)

```
Input: root = [3,9,20,null,null,15,7]
Output: 2
```

**Example 2:**

```
Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 105]`.
- `-1000 <= Node.val <= 1000`

## 题目大意

给定一个二叉树，找到它的最小的深度，

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明: 叶子节点是指没有子节点的节点。

## 解题思路

具体思路就是递归左右子树，找到最小深度

### Solution1: 

这个解法是参考霜神的：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0111.Minimum-Depth-of-Binary-Tree/

但是我个人觉得第二种解法的意思更明显，初学的话，看第二种解法可能更容易理解一点，当让，两种解法本质上是一样的



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
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        // 如果左子树为空，求右子树
        if (!root->left) {
            return minDepth(root->right) + 1;
        }
        // 如果右子树为空，求左子树
        if (!root->right) {
            return minDepth(root->left) + 1;
        }
        
        // 返回二者中的最小值 + 1
        return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};
`````

### Solution 2

递归的终止条件：

* 节点本身为空时返回 0
* 节点的为叶子节点时，返回 1
* 节点的左孩子为空时，返回右子树的深度 + 1
* 节点的右孩子为空时，返回左子树的深度 + 1
* 节点的左右孩子都不为空时，返回左右子树深度的最小值 + 1

具体参考代码

如果将 情况2 和情况 5 合并就是解法1

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
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        // 如果是叶子节点返回 1
        if (!root->left && !root->right) {
            return 1;
        }
        
        // 递归求解左右子树的深度
        int left_depth = root->left ? minDepth(root->left) : INT_MAX;
        int right_depth = root->right ? minDepth(root->right) : INT_MAX;
        
        return min(left_depth, right_depth) + 1;
    }
};
````

