# [129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/)

## 题目

You are given the `root` of a binary tree containing digits from `0` to `9` only.

Each root-to-leaf path in the tree represents a number.

- For example, the root-to-leaf path `1 -> 2 -> 3` represents the number `123`.

Return *the total sum of all root-to-leaf numbers*. Test cases are generated so that the answer will fit in a **32-bit** integer.

A **leaf** node is a node with no children.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/02/19/num1tree.jpg)

```
Input: root = [1,2,3]
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/02/19/num2tree.jpg)

```
Input: root = [4,9,0,5,1]
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 1000]`.
- `0 <= Node.val <= 9`
- The depth of the tree will not exceed `10`.

## 题目大意

给定一棵二叉树的根节点，每个节点包含 0 - 9 的数字，每一条从根节点到叶子节点的路径代表一个整数， 

- 例如，从根节点到叶节点的路径 `1 -> 2 -> 3` 表示数字 `123` 。

计算从根节点到叶节点生成的 **所有数字之和** 。

**叶节点** 是指没有子节点的节点。

## 解题思路

这道题可以采用前序遍历的方法来解决，具体思路是在递归的过程中，计算单条路径，当每条路径到达叶子节点，就将其加入到结果集中，

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
    int sumNumbers(TreeNode* root) {
        DFS(root, 0);
        return res_;
    }
    
 private:
    int res_;
    
    void DFS(TreeNode *root, int sum) {
        // 节点为空直接返回
        if (root == nullptr) {
            return;
        }
        
        // 加入当前节点
        sum = sum * 10 + root->val;
        // 如果是叶子节点，则加入结果中
        if (!root->left && !root->right) {
            res_ += sum;
            return;
        }
        
        DFS(root->left, sum);
        DFS(root->right, sum);
    }
};
````

