#### [1339. Maximum Product of Splitted Binary Tree](https://leetcode.cn/problems/maximum-product-of-splitted-binary-tree/)

## 题目

Given the `root` of a binary tree, split the binary tree into two subtrees by removing  one edge such that the product of the sums of the subtrees is maximized.

Return *the maximum product of the sums of the two subtrees*. Since the answer may be too large, return it **modulo** `109 + 7`.

**Note** that you need to maximize the answer before taking the mod and not after taking it.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/01/21/sample_1_1699.png)

```
Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2020/01/21/sample_2_1699.png)

```
Input: root = [1,null,2,3,4,null,null,5,6]
Output: 90
Explanation: Remove the red edge and get 2 binary trees with sum 15 and 6.Their product is 90 (15*6)
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[2, 5 * 104]`.
- `1 <= Node.val <= 104`

## 题目大意



给你一棵二叉树，它的根为 root 。请你删除 1 条边，使二叉树分裂成两棵子树，且它们子树和的乘积尽可能大。

由于答案可能会很大，请你将结果对 10^9 + 7 取模后再返回

## 解题思路

可以这样理解，删除一条边之后，可以将整棵树分为两个子树，一部分为一个子树的所有节点的和，另一部分是整棵树的和减去这个子树的所有节点的和

### Solution 1:

这道题目可以利用 后序遍历来解决，依次求出每个子树的和，并利用一个 set 来去重，最后返回结果的时候取模

`````c++
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def __init__(self):
        self.arr = set()
    
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        whole = self.dfs(root)
        
        ans = 0
        for total in self.arr:
            ans = max(ans, total * (whole - total))
            
        return ans % (10**9 + 7)
    
    def dfs(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        
        total = self.dfs(root.left) + self.dfs(root.right) + root.val
        self.arr.add(total)
        return total
`````

