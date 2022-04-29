# [971. Flip Binary Tree To Match Preorder Traversal](https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/)

## 题目

You are given the `root` of a binary tree with `n` nodes, where each node is uniquely assigned a value from `1` to `n`. You are also given a sequence of `n` values `voyage`, which is the **desired** [**pre-order traversal**](https://en.wikipedia.org/wiki/Tree_traversal#Pre-order) of the binary tree.

Any node in the binary tree can be **flipped** by swapping its left and right subtrees. For example, flipping node 1 will have the following effect:

![img](https://assets.leetcode.com/uploads/2021/02/15/fliptree.jpg)

Flip the **smallest** number of nodes so that the **pre-order traversal** of the tree **matches** `voyage`.

Return *a list of the values of all **flipped** nodes. You may return the answer in **any order**. If it is **impossible** to flip the nodes in the tree to make the pre-order traversal match* `voyage`*, return the list* `[-1]`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/01/02/1219-01.png)

```
Input: root = [1,2], voyage = [2,1]
Output: [-1]
Explanation: It is impossible to flip the nodes such that the pre-order traversal matches voyage.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/01/02/1219-02.png)

```
Input: root = [1,2,3], voyage = [1,3,2]
Output: [1]
Explanation: Flipping node 1 swaps nodes 2 and 3, so the pre-order traversal matches voyage.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/01/02/1219-02.png)

```
Input: root = [1,2,3], voyage = [1,2,3]
Output: []
Explanation: The tree's pre-order traversal already matches voyage, so no nodes need to be flipped.
```

 

**Constraints:**

- The number of nodes in the tree is `n`.
- `n == voyage.length`
- `1 <= n <= 100`
- `1 <= Node.val, voyage[i] <= n`
- All the values in the tree are **unique**.
- All the values in `voyage` are **unique**.

## 题目大意 

给你一棵二叉树的根节点 `root` ，树中有 `n` 个节点，每个节点都有一个不同于其他节点且处于 `1` 到 `n` 之间的值

另给你一个由 `n` 个值组成的行程序列 `voyage` ，表示 *预期* 的二叉树 *先序遍历* 结果

通过交换节点的左右子树，可以 *翻转* 该二叉树中的任意节点。请翻转 *最少* 的树中节点，使二叉树的 *先序遍历* 与预期的遍历行程 `voyage` 相匹配 

如果可以，则返回 *翻转的* 所有节点的值的列表, 你可以按任何顺序返回答案。如果不能，则返回列表 `[-1]`

## 解题思路

### Solution 1:

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0971.Flip-Binary-Tree-To-Match-Preorder-Traversal/)

这道题目就是贪心的思想，从根节点开始前序遍历，如果当前节点的值不匹配，直接返回 错误即可，如果下一个位置不匹配，就做交换，就可以保证最少的交换次数

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
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        // 这里的答案有 3 中状态，
        // 空集
        // -1
        // 结果集
        res_.clear();
        
        int idx = 0;
        if (PreOrder(root, voyage, idx)) {
            return res_;
        }
        
        return {-1};
    }
    
 private:
    vector<int> res_;
    
    // 前续遍历
    bool PreOrder(TreeNode *root, const vector<int>& voyage, int& idx) {
        // 如果为空，返回 true
        if (!root) {
            return true;
        }
        // 如果值不匹配，返回 false
        if (root->val != voyage[idx]) {
            return false;
        }
        
        ++idx;
        
        // 如果下一个节点的而值不匹配，做交换，并将当前节点加入到结果集中
        if (root->left && root->left->val != voyage[idx]) {
            res_.push_back(root->val);
            return PreOrder(root->right, voyage, idx) && PreOrder(root->left, voyage, idx);
        }
        
        // 如果是匹配的，那么就继续前序遍历
        return PreOrder(root->left, voyage, idx) && PreOrder(root->right, voyage, idx);
    }
};
````
