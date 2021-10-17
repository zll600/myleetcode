# [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)

## 题目

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

> a binary tree in which the left and right subtrees of *every* node differ in height by no more than 1.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/10/06/balance_1.jpg)

```
Input: root = [3,9,20,null,null,15,7]
Output: true
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/10/06/balance_2.jpg)

```
Input: root = [1,2,2,3,3,null,null,4,4]
Output: false
```

**Example 3:**

```
Input: root = []
Output: true
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[0, 5000]`.
- `-104 <= Node.val <= 104`

## 题目大意

给定一棵二叉树，判断这棵儿叉树是不是平衡的

平衡二叉树的定义是：每个节点左子树和右子树的高度相差不超过 1

## 解题思路

这道题的解法可以参考这两篇题解：https://zxi.mytechroad.com/blog/leetcode/leetcode-110-balanced-binary-tree/

### Solution1

这道题可以联系第 104 题，计算每个节点的左子树和右子树的深度，然后做判断，我觉得这里会有大量的重复计算

这里采用的先序遍历，

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
    bool isBalanced(TreeNode* root) {
        if (!root) {
           return true;
        }
        // 左子树高度
        int left_height = GetDepth(root->left);
        // 右子树高度
        int right_height = GetDepth(root->right);
        
        return abs(left_height - right_height) <= 1
            && isBalanced(root->left) && isBalanced(root->right);
    }
    
 private:
    int GetDepth(TreeNode *root) {
        if (!root) {
            return 0;
        }
        
        return max(GetDepth(root->left), GetDepth(root->right)) + 1;
    }
};
````

### Solution 2:

这种解法采用的后序遍历，先递归判断左子树是否符合条件，然后递归判断右子树是否符合条件，只有当左子树和右子树都各自符合条件才检查当前节点是否符合条件，因为这里就将判断是否符合条件放在计算节点的高度上，所以这里使用 -1 作为标识符表示左子树或者右子树中已经不满足条件，则不用继续递归下去

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
    bool isBalanced(TreeNode* root) {
        if (!root) {
           return true;
        }
        bool res = true;
        IsBalanced(root, res);
        return res;
    }
    
 private:
    int IsBalanced(TreeNode *root, bool& res) {
        if (!root) {
            return 0;
        }
        // 递归判断左子树
        int left_height = IsBalanced(root->left, res);
        // 剪枝
        if (!res) {
            return -1;
        }
        
        // 递归判断右子树
        int right_height = IsBalanced(root->right, res);
        // 剪枝
        if (!res) {
            return -1;
        }
        
        // 判断当前节点
        if (abs(left_height - right_height) > 1) {
            res = false;
            return -1;
        }
        
        return max(left_height, right_height) + 1;
    }
};
`````

