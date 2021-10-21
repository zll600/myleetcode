# [112. Path Sum](https://leetcode.com/problems/path-sum/)

## 题目

Given the `root` of a binary tree and an integer `targetSum`, return `true` if the tree has a **root-to-leaf** path such that adding up all the values along the path equals `targetSum`.

A **leaf** is a node with no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/18/pathsum1.jpg)

```
Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/18/pathsum2.jpg)

```
Input: root = [1,2,3], targetSum = 5
Output: false
```

**Example 3:**

```
Input: root = [1,2], targetSum = 0
Output: false
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 5000]`.
- `-1000 <= Node.val <= 1000`
- `-1000 <= targetSum <= 1000`

## 题目大意

给定一棵二叉树的根节点 root 和一个整数 targetSum，如果这棵树存在一条从根节点到叶子节点的路径和为 targetSum 就返回true，

## 解题思路

### Solution 1:

我们可以在递归的过程中不断减小目标值，直到和最后一个值相等为止，这里需要注意的是，这个变量是在一条路径上改变，而非是整棵树，所以需要回溯，遍历完左子树，要恢复到之前，然后遍历右子树

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
    bool hasPathSum(TreeNode *root, int targetSum) {
        return DFS(root, targetSum);
    }
    
 private:
    bool DFS(TreeNode *root, int target) {
        if (!root) {
            return false;
        }
        
        // 如果是叶子节点，则进行判断
        if (!root->left && !root->right) {
            return target == root->val;
        }
        
        // 递归的向两边求解
        return DFS(root->left, target - root->val) || DFS(root->right, target - root->val);
    }
};
````

