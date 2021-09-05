# [530. Minimum Absolute Difference in BST](https://leetcode.com/problems/minimum-absolute-difference-in-bst/)

## 题目

Given the `root` of a Binary Search Tree (BST), return *the minimum absolute difference between the values of any two different nodes in the tree*.

 

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

- The number of nodes in the tree is in the range `[2, 104]`.
- `0 <= Node.val <= 105`

 

**Note:** This question is the same as 783: https://leetcode.com/problems/minimum-distance-between-bst-nodes/

## 题目大意

给定一棵二叉搜索树，计算任意两个节点的差值的绝对值的最小值

## 解题思路

* 这道题目和第 783 相近，可一起参考

* 利用二叉搜索树中序遍历的有序行，找出最小的差值

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
    int getMinimumDifference(TreeNode* root) {
        res = INT_MAX;
        int pre = -1;
        DFS(root, &pre);
        return res;
    }
    
 private:
    int res;
    
    // 这里 pre 要在整个遍历过程中变化，所以必须传引用，
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

