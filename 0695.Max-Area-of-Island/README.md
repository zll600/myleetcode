# [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)

## 题目

You are given an `m x n` binary matrix `grid`. An island is a group of `1`'s (representing land) connected **4-directionally** (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The **area** of an island is the number of cells with a value `1` in the island.

Return *the maximum **area** of an island in* `grid`. If there is no island, return `0`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/01/maxarea1-grid.jpg)

```
Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.
```

**Example 2:**

```
Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 50`
- `grid[i][j]` is either `0` or `1`.

## 题目大意

给定一个 `m x n` 的矩形 `grid`，一个 岛屿 是由一些相邻的 `1 (代表土地) ` 构成的组合，这里的 `「相邻」`要求两个 `1` 必须在 *水平或者竖直* 方向上相邻。你可以假设 `grid` 的四个边缘都被 `0（代表水）` 包围着。

岛屿的面积就是岛屿中值为 `1` 的方格的数目

找到给定的 `grid` 中最大的岛屿面积。(如果没有岛屿，则返回 `0` 。)

## 解题思路

这道题目就是 利用 DFS 深搜来做，DFS 所有的岛屿，然后保留最大值

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0695.Max-Area-of-Island/)

这里需要注意的就是如果当前这一轮的递归如果依赖于下一论递归的结果，可以使用返回值来将下一论的递归结果传到这一轮中

````c++
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        // 先统计每个字符串出现的频数
        unordered_map<string, int> freqs;
        for (const string& word : words) {
            ++freqs[word];
        }

        // 这里将字符串和其出现的频数做一个绑定
        vector<pair<string, int>> records(freqs.begin(), freqs.end());
        // 对已经建立好的集合进行排序
        sort(records.begin(), records.end(),
             [](const pair<string, int>& lhs, const pair<string, int>& rhs) {
                 if (lhs.second != rhs.second) {
                     // 按照频数的降序
                     return lhs.second > rhs.second;
                 } else {
                     // 频数相同按照字典序
                     return lhs.first < rhs.first;
                 }
             });

        // 这里直接取够所有的即可
        const int len = records.size();
        vector<string> res;
        // 这里遍历的上界要注意，这道题目有说明，如果没有说明需要考虑到
        for (int i = 0; i < min(k, len); ++i) {
            res.push_back(records[i].first);
        }

        return res;
    }
};
````
