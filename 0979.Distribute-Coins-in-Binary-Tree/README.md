# [979. Distribute Coins in Binary Tree](https://leetcode.com/problems/distribute-coins-in-binary-tree/)

## 题目

You are given the `root` of a binary tree with `n` nodes where each `node` in the tree has `node.val` coins. There are `n` coins in total throughout the whole tree.

In one move, we may choose two adjacent nodes and move one coin from  one node to another. A move may be from parent to child, or from child  to parent.

Return *the **minimum** number of moves required to make every node have **exactly** one coin*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/01/18/tree1.png)

```
Input: root = [3,0,0]
Output: 2
Explanation: From the root of the tree, we move one coin to its left child, and one coin to its right child.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/01/18/tree2.png)

```
Input: root = [0,3,0]
Output: 3
Explanation: From the left child of the root, we move two coins to the root [taking two moves]. Then, we move one coin from the root of the tree to the right child.
```

 

**Constraints:**

- The number of nodes in the tree is `n`.
- `1 <= n <= 100`
- `0 <= Node.val <= n`
- The sum of all `Node.val` is `n`.

## 题目大意

给定一个有 `N` 个结点的二叉树的根结点 `root`，树中的每个结点上都对应有 `node.val` 枚硬币，并且总共有 `N` 枚硬币。

在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点。(移动可以是从父结点到子结点，或者从子结点移动到父结点。)

返回使每个结点上只有一枚硬币所需的移动次数

## 解题思路



### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0979.Distribute-Coins-in-Binary-Tree/)

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
    int distributeCoins(TreeNode* root) {
        int res = 0;
        DFS(root, res);
        return res;
    }
    
 private:
    int DFS(TreeNode *root, int& res) {
        if (!root) {
            return 0;   
        }
        
        int left_res = DFS(root->left, res);
        int right_res = DFS(root->right, res);
        res += abs(left_res) + abs(right_res);
        return left_res + right_res + root->val - 1;
    }
};
````

