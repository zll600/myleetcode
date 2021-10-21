# [113. Path Sum II](https://leetcode.com/problems/path-sum-ii/)

Given the `root` of a binary tree and an integer `targetSum`, return *all **root-to-leaf** paths where the sum of the node values in the path equals* `targetSum`*. Each path should be returned as a list of the node **values**, not node references*.

A **root-to-leaf** path is a path starting from the root and ending at any leaf node. A **leaf** is a node with no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/18/pathsumii1.jpg)

```
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/18/pathsum2.jpg)

```
Input: root = [1,2,3], targetSum = 5
Output: []
```

**Example 3:**

```
Input: root = [1,2], targetSum = 0
Output: []
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 5000]`.
- `-1000 <= Node.val <= 1000`
- `-1000 <= targetSum <= 1000`

## 题目大意

给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。说明: 叶子节点是指没有子节点的节点。

## 解题思路

这里放上霜神的一句话：

- 这一题是第 257 题和第 112 题的组合增强版

### Solution 1:

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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            vector<vector<int>>();
        }
        DFS(root, targetSum);
        return res_;
    }
    
private:
    vector<vector<int>> res_;
    vector<int> path_;
    
    void DFS(TreeNode *root, int target) {
        if (!root) {  // 边界条件
            return;
        }
        
        path_.push_back(root->val);
        if (!root->left && !root->right) {
            if (target == root->val) {
                res_.push_back(path_);
            }
        }
        
        // 递归左子树
        DFS(root->left, target - root->val);
        // 递归右子树
        DFS(root->right, target - root->val);
        
        path_.pop_back();  // 回溯
    }
};
````

