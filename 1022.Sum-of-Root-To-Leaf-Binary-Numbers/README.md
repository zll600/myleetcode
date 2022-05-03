#### [1022. Sum of Root To Leaf Binary Numbers](https://leetcode-cn.com/problems/sum-of-root-to-leaf-binary-numbers/)

You are given the `root` of a binary tree where each node has a value `0` or `1`. Each root-to-leaf path represents a binary number starting with the most significant bit.

- For example, if the path is `0 -> 1 -> 1 -> 0 -> 1`, then this could represent `01101` in binary, which is `13`.

For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return *the sum of these numbers*.

The test cases are generated so that the answer fits in a **32-bits** integer.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/04/04/sum-of-root-to-leaf-binary-numbers.png)

```
Input: root = [1,0,1,0,1,0,1]
Output: 22
Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
```

**Example 2:**

```
Input: root = [0]
Output: 0
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 1000]`.
- `Node.val` is `0` or `1`.

## 题目大意

给出一棵二叉树，其上每个结点的值都是 `0` 或 `1` 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数

- 例如，如果路径为 `0 -> 1 -> 1 -> 0 -> 1`，那么它表示二进制数 `01101`，也就是 `13` 

对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字

返回这些数字之和。题目数据保证答案是一个 `32` 位 整数

### 解题思路


### Solution 1: Preorder traversal


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
    int sumRootToLeaf(TreeNode* root) {
        res_ = 0;
        DFS(root, 0);
        return res_;
    }

 private:
    int res_;

    void DFS(TreeNode *root, int cur) {
        if (!root) {
            return;
        }

        // 记录每条路径上的值
        cur = (cur << 1) + root->val;
        // 如果遇到叶子节点，则进行累加
        if (!root->left && !root->right) {
            res_ += cur;
            return;
        }
        DFS(root->left, cur);
        DFS(root->right, cur);
    }
};
````
