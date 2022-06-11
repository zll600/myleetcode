# [998. Maximum Binary Tree II](https://leetcode.cn/problems/maximum-binary-tree-ii/)

## 题目

A **maximum tree** is a tree where every node has a value greater than any other value in its subtree.

You are given the `root` of a maximum binary tree and an integer `val`.

Just as in the [previous problem](https://leetcode.com/problems/maximum-binary-tree/), the given tree was constructed from a list `a` (`root = Construct(a)`) recursively with the following `Construct(a)` routine:

- If `a` is empty, return `null`.
- Otherwise, let `a[i]` be the largest element of `a`. Create a `root` node with the value `a[i]`.
- The left child of `root` will be `Construct([a[0], a[1], ..., a[i - 1]])`.
- The right child of `root` will be `Construct([a[i + 1], a[i + 2], ..., a[a.length - 1]])`.
- Return `root`.

Note that we were not given `a` directly, only a root node `root = Construct(a)`.

Suppose `b` is a copy of `a` with the value `val` appended to it. It is guaranteed that `b` has unique values.

Return `Construct(b)`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/08/09/maxtree1.JPG)

```
Input: root = [4,1,3,null,null,2], val = 5
Output: [5,4,null,1,3,null,null,2]
Explanation: a = [1,4,2,3], b = [1,4,2,3,5]
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/08/09/maxtree21.JPG)

```
Input: root = [5,2,4,null,1], val = 3
Output: [5,2,4,null,1,null,3]
Explanation: a = [2,1,5,4], b = [2,1,5,4,3]
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/08/09/maxtree3.JPG)

```
Input: root = [5,2,3,null,1], val = 4
Output: [5,2,4,null,1,3]
Explanation: a = [2,1,5,3], b = [2,1,5,3,4]
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 100]`.
- `1 <= Node.val <= 100`
- All the values of the tree are **unique**.
- `1 <= val <= 100`

## 题目大意

最大树 定义：一棵树，并满足：其中每个节点的值都大于其子树中的任何其他值

给你最大树的根节点 `root` 和一个整数 `val`

就像 之前的问题 那样，给定的树是利用 `Construct(a)` 例程从列表 `a（root = Construct(a)）` 递归地构建的：

-   如果 `a` 为空，返回 `null`
-   否则，令 `a[i]` 作为 `a` 的最大元素。创建一个值为 `a[i]` 的根节点 `root`
-   root 的左子树将被构建为 `Construct([a[0], a[1], ..., a[i - 1]])`
-   root 的右子树将被构建为 `Construct([a[i + 1], a[i + 2], ..., a[a.length - 1]])`
-   返回 `root`

请注意，题目没有直接给出 `a` ，只是给出一个根节点 `root = Construct(a)`

假设 `b` 是 `a` 的副本，并在末尾附加值 `val`。题目数据保证 `b` 中的值互不相同

返回 Construct(b)

### Solution 1:


这道题目可以参考 [这篇题解](https://leetcode.cn/problems/maximum-binary-tree-ii/solution/998-czhong-gui-zhong-ju-de-di-gui-jie-fa-5pfq/)

根据题目给出的 3 中例子，也可以总结出

- `root` 为空，root 作为新节点的左节点
- `root->val < val`，root 作为新节点左节点
- 其余情况递归到 root 的右子树中判断

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
    TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
        // 如果 root 为空，或者 val > root->val
        // 将root 作为新节点的左子树
        // 看 example1 和 example2
        if (root == nullptr || val > root->val) {
            TreeNode *new_node = new TreeNode(val);
            new_node->left = root;
            return new_node;
        }

        // 否则递归到 root 的友子树中继续查找
        root->right =  insertIntoMaxTree(root->right, val);
        return root;
    }
};
````
