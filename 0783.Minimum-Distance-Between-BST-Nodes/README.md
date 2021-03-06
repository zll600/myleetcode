# [783. Minimum Distance Between BST Nodes](https://leetcode.com/problems/minimum-distance-between-bst-nodes/) 

Given the `root` of a Binary Search Tree (BST), return *the minimum difference between the values of any two different nodes in the tree*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/05/bst1.jpg)

```
Input: root = [4,2,6,1,3]
Output: 1
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/05/bst2.jpg)

```
Input: root = [1,0,48,null,null,12,49]
Output: 1
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[2, 100]`.
- `0 <= Node.val <= 105`

 

**Note:** This question is the same as 530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/

## 题目大意

给定棵二叉查找树，返回任意两个节点值的差值的最小值，

## 解题思路

* 这道题和第 530 题简直一模一样，可以参考那道题的解释

## 代码

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
    int minDiffInBST(TreeNode* root) {
        res = INT_MAX;
        int pre = -1;
        
        DFS(root, &pre);
        return res;
    }
    
 private:
    int res = 0;
    
    void DFS(TreeNode *root, int *pre) {
        if (root == nullptr) {
            return;
        }
        
        DFS(root->left, pre);
        
        if (*pre != -1) {
            res = min(res, abs(root->val - *pre));
        }
        *pre = root->val;
        
        DFS(root->right, pre);
    }
};
````

