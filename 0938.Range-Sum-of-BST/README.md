# [938. Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/)

Given the `root` node of a binary search tree and two integers `low` and `high`, return *the sum of values of all nodes with a value in the **inclusive** range* `[low, high]`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/11/05/bst1.jpg)

```
Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
Output: 32
Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/11/05/bst2.jpg)

```
Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
Output: 23
Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 2 * 104]`.
- `1 <= Node.val <= 105`
- `1 <= low <= high <= 105`
- All `Node.val` are **unique**.

## 题目大意

给定一棵二叉查找树，返回所有出现在[low, high] 区间的节点的值的和。

## 解题思路

* 这道题只需要遍历整棵数，对每个节点判断是否合理即可，但利用中序便利的有序行，可以做剪枝优化，但是不能降低时空复杂度。

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
    int rangeSumBST(TreeNode* root, int low, int high) {
        res = 0;
        
        // DFS(root, low, high);
        // return res;
        return Pruning(root, low, high);
    }
    
 private:
    int res;
    
    void DFS(TreeNode *root, int low, int high) {
        if (root == nullptr) {
            return;
        }
            
        DFS(root->left, low, high);
        
        if (low <= root->val && root->val <= high) {
            res += root->val;
        }
        
        DFS(root->right, low, high);
    }
    
    // 这种写法可以做到剪枝优化，但并不影响时空复杂度
    int Pruning(TreeNode *root, int low, int high) {
        if (root == nullptr) {
            return 0;
        }
        
        if (root->val < low) {
            return Pruning(root->right, low, high);
        }
        if (root->val > high) {
            return Pruning(root->left, low, high);
        }
        
        return root->val + Pruning(root->left, low, high) + Pruning(root->right, low, high);
    }
};
````

