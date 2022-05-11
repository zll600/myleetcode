# [1123. Lowest Common Ancestor of Deepest Leaves](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/)

## 题目

Given the `root` of a binary tree, return *the lowest common ancestor of its deepest leaves*.

Recall that:

- The node of a binary tree is a leaf if and only if it has no children
- The depth of the root of the tree is `0`. if the depth of a node is `d`, the depth of each of its children is `d + 1`.
- The lowest common ancestor of a set `S` of nodes, is the node `A` with the largest depth such that every node in `S` is in the subtree with root `A`.

 

**Example 1:**

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/01/sketch1.png)

```
Input: root = [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation: We return the node with value 2, colored in yellow in the diagram.
The nodes coloured in blue are the deepest leaf-nodes of the tree.
Note that nodes 6, 0, and 8 are also leaf nodes, but the depth of them is 2, but the depth of nodes 7 and 4 is 3.
```

**Example 2:**

```
Input: root = [1]
Output: [1]
Explanation: The root is the deepest node in the tree, and it's the lca of itself.
```

**Example 3:**

```
Input: root = [0,1,3,null,2]
Output: [2]
Explanation: The deepest leaf node in the tree is 2, the lca of one node is itself.
```

 

**Constraints:**

- The number of nodes in the tree will be in the range `[1, 1000]`.
- `0 <= Node.val <= 1000`
- The values of the nodes in the tree are **unique**.

 

**Note:** This question is the same as 865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/


## 题目大意

给你一个有根节点 `root` 的二叉树，返回它 *最深的叶节点的最近公共祖先*。

回想一下：

- 叶节点 是二叉树中没有子节点的节点
- 树的根节点的 深度 为 `0`，如果某一节点的深度为 `d`，那它的子节点的深度就是 `d+1`
- 如果我们假定 `A` 是一组节点 `S` 的 最近公共祖先，`S` 中的每个节点都在以 `A` 为根节点的子树中，且 `A` 的深度达到此条件下可能的最大值

## 解题思路

### Solution 1: Tree

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1100~1199/1123.Lowest-Common-Ancestor-of-Deepest-Leaves/)

这种解法使用的就是 二叉树的后序遍历来做，先分别求得左子树和右子树的最大深度，然后进行判断，和最大深度相等的节点的父节点就是我们要找的答案

这里注意，递归的 base case 之前需要更新 maxLevel，否则会出现左右子树的深度和 maxLevel 不相等的情况

````Go
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func lcaDeepestLeaves(root *TreeNode) *TreeNode {
    lca, maxLevel := &TreeNode{}, 0
    lcaDeepestLeavesPostOrder(root, &maxLevel, 0, &lca)
    return lca
}

func lcaDeepestLeavesPostOrder(root *TreeNode, maxLevel *int, depth int, lca **TreeNode) int {
    *maxLevel = max(*maxLevel, depth)
    if root == nil {
        return depth
    }

    depthLeft := lcaDeepestLeavesPostOrder(root.Left, maxLevel, depth + 1, lca)
    depthRight := lcaDeepestLeavesPostOrder(root.Right, maxLevel, depth + 1, lca)
    // fmt.Println(root.Val, " depth is ", depth, " maxLevel is ", *maxLevel)
    if depthLeft == *maxLevel && depthRight == *maxLevel {
        *lca = root
    }
    return max(depthLeft, depthRight)
}

func max(a, b int) int {
    if b > a {
        return b
    }
    return a
}
````
