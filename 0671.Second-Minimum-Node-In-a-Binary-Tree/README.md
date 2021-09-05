# [671. Second Minimum Node In a Binary Tree](https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/)

## 题目

Given a non-empty special binary tree consisting of nodes with the non-negative value, where each node in this tree has exactly `two` or `zero` sub-node. If the node has two sub-nodes, then this node's value is the smaller value among its two sub-nodes. More formally, the property `root.val = min(root.left.val, root.right.val)` always holds.

Given such a binary tree, you need to output the **second minimum** value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

 

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/15/smbt1.jpg)

```
Input: root = [2,2,5,null,null,5,7]
Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/15/smbt2.jpg)

```
Input: root = [2,2,2]
Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 25]`.
- `1 <= Node.val <= 231 - 1`
- `root.val == min(root.left.val, root.right.val)` for each internal node of the tree.

## 题目大意

给定一个非空二叉树，书中节点的值都为正，每个节点只能有 2 或者 0 子节点，节点的值等于字节点中较小的一个，找到二叉树中第二小的值，如果没有返回 -1，

## 解题思路

根据**每个节点都式子节点的最小值**的性质，所以根节点一定式最小的节点，且越靠近根节点，值越小，越接近根节点的值，同时要避免**节点和其子节点**的值完相等的情况。

这道题目使用 DFS 深搜前序遍历，加剪枝优化

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
    int findSecondMinimumValue(TreeNode* root) {
        if (root->left == nullptr && root->right == nullptr) {
            return -1;
        }
        
        res = -1;
        DFS(root, root->val);
        
        return res;
    }
    
 private:
    int res;
    
    void DFS(TreeNode *root, int target) {
        if (root == nullptr) {
            return;
        }
        
        if (root->val != target) {
            if (res == -1) {
                res = root->val;
            } else {
                res = min(res, root->val);
            }
            return; // 剪枝操作，如果给 res 赋了新值，或者更小的值，则可以直接返回，只与前序遍历结合
        }
        
        DFS(root->left, target);
        DFS(root->right, target);
    }
};
````

