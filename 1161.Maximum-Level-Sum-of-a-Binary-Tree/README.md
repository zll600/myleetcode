# [1161. Maximum Level Sum of a Binary Tree](https://leetcode.cn/problems/maximum-level-sum-of-a-binary-tree/)

## 题目

Given the `root` of a binary tree, the level of its root is `1`, the level of its children is `2`, and so on.

Return the **smallest** level `x` such that the sum of all the values of nodes at level `x` is **maximal**.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/05/03/capture.JPG)

```
Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.
```

**Example 2:**

```
Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
Output: 2
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 104]`.
- `-105 <= Node.val <= 105`

## 题目大意

给你一个二叉树的根节点 `root`。设根节点位于二叉树的第 `1` 层，而根节点的子节点位于第 `2` 层，依此类推

请返回层内元素之和 最大 的那几层（可能只有一层）的层号，并返回其中 最小 的那个

## 解题思路

这道题目应该不难想到使用 层序遍历来做

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
    int maxLevelSum(TreeNode* root) {
        int res = 0;
        int sum = INT_MIN;
        int level = 0;
        
        queue<TreeNode*> que;
        que.push(root);
        while (!que.empty()) {
            ++level;
            const int len = que.size();
            int total = 0;
            for (int i = 0; i < len; ++i) {
                TreeNode *cur = que.front();
                que.pop();
                
                total += cur->val;
                
                if (cur->left) {
                    que.push(cur->left);
                }
                if (cur->right) {
                    que.push(cur->right);
                }
            }

            // cout << total << endl;
            if (total > sum) {
                sum = total;
                res = level;
            }
        }
        return res;
    }
};
```
