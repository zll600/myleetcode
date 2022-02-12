# [662. Maximum Width of Binary Tree](https://leetcode.com/problems/maximum-width-of-binary-tree/)

## 题目

Given the `root` of a binary tree, return *the **maximum width** of the given tree*.

The **maximum width** of a tree is the maximum **width** among all levels.

The **width** of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes are also counted into the length calculation.

It is **guaranteed** that the answer will in the range of **32-bit** signed integer.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/03/width1-tree.jpg)

```
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/03/width2-tree.jpg)

```
Input: root = [1,3,null,5,3]
Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/05/03/width3-tree.jpg)

```
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
```

 

**Constraints:**

- The number of nodes in the tree is in the range `[1, 3000]`.
- `-100 <= Node.val <= 100`

## 题目大意

给定一棵二叉树的根节点，返回给定树的最大宽度

树的宽度是所有层的最大宽度，

**宽度** 被定义为每一层的最左边和最右边的非空节点，边界节点之间的所有空节点也没被计算在宽度之中，

题目保证，答案可以用 32 为整数来表示，

## 解题思路

这道题主要就是求出每一层的最左边和最右边的位置，然后做差即可，这里的话，因为 每个节点的 val 其实是用不到的，所以这里其实可以直接覆盖 val 的值来做序号，


### Solution 1: BFS

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0662.Maximum-Width-of-Binary-Tree/)

这种解法不适合直接采用C++ 来写，所以可以考虑换其他的方法、


````c++
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func widthOfBinaryTree(root *TreeNode) int {
	if root == nil {
		return 0
	}
	if root.Left == nil && root.Right == nil {
		return 1
	}

	queue, res := []*TreeNode{}, 0
	queue = append(queue, &TreeNode{0, root.Left, root.Right})

	for len(queue) != 0 {
		var left, right *int
		// 这里需要注意，先保存 queue 的个数，相当于拿到此层的总个数
		qLen := len(queue)
		// 这里循环不要写 i < len(queue)，因为每次循环 queue 的长度都在变小
		for i := 0; i < qLen; i++ {
			node := queue[0]
			queue = queue[1:]
			if node.Left != nil {
				// 根据满二叉树父子节点的关系，得到下一层节点在本层的编号
				newVal := node.Val * 2
				queue = append(queue, &TreeNode{newVal, node.Left.Left, node.Left.Right})
				if left == nil || *left > newVal {
					left = &newVal
				}
				if right == nil || *right < newVal {
					right = &newVal
				}
			}
			if node.Right != nil {
				// 根据满二叉树父子节点的关系，得到下一层节点在本层的编号
				newVal := node.Val*2 + 1
				queue = append(queue, &TreeNode{newVal, node.Right.Left, node.Right.Right})
				if left == nil || *left > newVal {
					left = &newVal
				}
				if right == nil || *right < newVal {
					right = &newVal
				}
			}
		}
		switch {
		// 某层只有一个点，那么此层宽度为 1
		case left != nil && right == nil, left == nil && right != nil:
			res = max(res, 1)
		// 某层只有两个点，那么此层宽度为两点之间的距离
		case left != nil && right != nil:
			res = max(res, *right-*left+1)
		}
	}
	return res
}

func max(a, b int) int {
    if (a > b) {
        return a
    }
    return b
}

````
