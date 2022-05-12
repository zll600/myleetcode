# [1145. Binary Tree Coloring Game](https://leetcode.com/problems/binary-tree-coloring-game/)

## 题目

Two players play a turn based game on a binary tree. We are given the `root` of this binary tree, and the number of nodes `n` in the tree. `n` is odd, and each node has a distinct value from `1` to `n`.

Initially, the first player names a value `x` with `1 <= x <= n`, and the second player names a value `y` with `1 <= y <= n` and `y != x`. The first player colors the node with value `x` red, and the second player colors the node with value `y` blue.

Then, the players take turns starting with the first player. In each  turn, that player chooses a node of their color (red if player 1, blue  if player 2) and colors an **uncolored** neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)

If (and only if) a player cannot choose such a node in this way, they must pass their turn. If both players pass their turn, the game ends,  and the winner is the player that colored more nodes.

You are the second player. If it is possible to choose such a `y` to ensure you win the game, return `true`. If it is not possible, return `false`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/08/01/1480-binary-tree-coloring-game.png)

```
Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
Output: true
Explanation: The second player can choose the node with value 2.
```

**Example 2:**

```
Input: root = [1,2,3], n = 3, x = 1
Output: false
```

 

**Constraints:**

- The number of nodes in the tree is `n`.
- `1 <= x <= n <= 100`
- `n` is odd.
- 1 <= Node.val <= n
- All the values of the tree are **unique**.

## 题目大意

有两位极客玩家参与了一场「二叉树着色」的游戏。游戏中，给出二叉树的根节点 root，树上总共有 n 个节点，且 n 为奇数，其中每个节点上的值从 1 到 n 各不相同。游戏从「一号」玩家开始（「一号」玩家为红色，「二号」玩家为蓝色），最开始时，

    「一号」玩家从 [1, n] 中取一个值 x（1 <= x <= n）；
    「二号」玩家也从 [1, n] 中取一个值 y（1 <= y <= n）且 y != x。
    「一号」玩家给值为 x 的节点染上红色，而「二号」玩家给值为 y 的节点染上蓝色。

之后两位玩家轮流进行操作，每一回合，玩家选择一个他之前涂好颜色的节点，将所选节点一个 未着色 的邻节点（即左右子节点、或父节点）进行染色。如果当前玩家无法找到这样的节点来染色时，他的回合就会被跳过。若两个玩家都没有可以染色的节点时，游戏结束。着色节点最多的那位玩家获得胜利 ✌️。现在，假设你是「二号」玩家，根据所给出的输入，假如存在一个 y 值可以确保你赢得这场游戏，则返回 true；若无法获胜，就请返回 false。

## 解题思路

不难想到，在 x 确定之后，y 可以放置的地方有几个位置

- x 的左子树（如果存在的话）
- x 的右子树（如果存在的话）
- 除了上面两个和 x 位置的其余连通的部分

只要这 3 个地方中有一个部分的节点数大于总节点数的 2 分之一，那么就可以获胜，

另外这里其实也存在一个贪心的思想，即我们在这个 3 个部分中总会选择靠近 x 的位置来放 y，这样可以限制 x 可以涂颜色的节点，增加 y 可以涂颜色的节点

所以接下来就是解决如果求出每个部分的节点数，x 的左子树或者右子树的节点数 leftCnt, rightCnt, 我们可以通过后序遍历整棵树然后在遍历 到 x 的时候更新这两个值，第三部分的值就是 n - leftCnt - rightCnt - 1

### Solution 1: DFS

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1100~1199/1145.Binary-Tree-Coloring-Game/)

````Go
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func btreeGameWinningMove(root *TreeNode, n int, x int) bool {
    var retLeft, retRight int
    dfsBtreeGameWinningMove(root, &retLeft, &retRight, x)
    other := n - retLeft - retRight - 1
    m := n / 2
    return retLeft > m || retRight > m || other > m
}

func dfsBtreeGameWinningMove(root *TreeNode,  retLeft, retRight *int, x int) int {
    if root == nil {
        return 0
    }
    // 统计节点的个数
    leftCnt, rightCnt := dfsBtreeGameWinningMove(root.Left, retLeft, retRight, x), dfsBtreeGameWinningMove(root.Right, retLeft, retRight, x)

    // 递归过程中需要注意我们要求出 x 点的个数
    if root.Val == x {
        *retLeft, *retRight = leftCnt, rightCnt
    }

    return leftCnt + rightCnt + 1
}
````
