# [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)

## 题目

Given the `root` of a binary tree, return *an array of the largest value in each row* of the tree **(0-indexed)**.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/08/21/largest_e1.jpg)

```
Input: root = [1,3,2,5,3,null,9]
Output: [1,3,9]
```

**Example 2:**

```
Input: root = [1,2,3]
Output: [1,3]
```

 

**Constraints:**

- The number of nodes in the tree will be in the range `[0, 104]`.
- `-231 <= Node.val <= 231 - 1`

## 题目大意

找出二叉树中每一行的最大值

## 解题思路

这道题显然是二叉树的层序遍历，在遍历每一层的节点的同时，更新和维护当前层的最大值即可

### Solution1: BFS

采用层序遍历，然后在遍历的过程中更新和维护最大值

````C++
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
    vector<int> largestValues(TreeNode* root) {
        if (!root) {
            // 特殊条件判断
            return {};
        }
        vector<int> res;
        queue<TreeNode*> que;
        que.push(root);

        while (!que.empty()) {
            int max_val = INT_MIN;
            const int len = que.size();

            for (int i = 0; i < len; ++i) {
                TreeNode *cur = que.front();
                que.pop();

                max_val = max(max_val, cur->val);

                if (cur->left) {
                    que.push(cur->left);
                }
                if (cur->right) {
                    que.push(cur->right);
                }
            }
            res.push_back(max_val);
        }
        return move(res);
    }
};
