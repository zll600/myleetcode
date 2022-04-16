# [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)

## 题目

There is an undirected connected tree with `n` nodes labeled from `0` to `n - 1` and `n - 1` edges.

You are given the integer `n` and the array `edges` where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the tree.

Return an array `answer` of length `n` where `answer[i]` is the sum of the distances between the `ith` node in the tree and all other nodes.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-sumdist1.jpg)

```
Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-sumdist2.jpg)

```
Input: n = 1, edges = []
Output: [0]
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-sumdist3.jpg)

```
Input: n = 2, edges = [[1,0]]
Output: [1,1]
```

 

**Constraints:**

- `1 <= n <= 3 * 104`
- `edges.length == n - 1`
- `edges[i].length == 2`
- `0 <= ai, bi < n`
- `ai != bi`
- The given input represents a valid tree.

## 题目大意

给定一个 *无向、连通* 的树。树中有 `N` 个标记为 `0…N-1` 的节点以及 `N-1` 条边。第 `i` 条边连接节点 `edges[i][0]` 和 `edges[i][1]` 。

返回一个表示节点 `i` 与其他所有节点距离之和的列表 `ans`。

## 解题思路

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0834.Sum-of-Distances-in-Tree/)

### Solution 1:


````c++

````
