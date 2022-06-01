# [799. Champagne Tower](https://leetcode.cn/problems/champagne-tower/)

## 题目

We stack glasses in a pyramid, where the **first** row has `1` glass, the **second** row has `2` glasses, and so on until the 100th row. Each glass holds one cup of champagne.

Then, some champagne is poured into the first glass at the top. When the topmost glass is full, any excess liquid poured will fall equally  to the glass immediately to the left and right of it. When those  glasses become full, any excess champagne will fall equally to the left  and right of those glasses, and so on. (A glass at the bottom row has  its excess champagne fall on the floor.)

For example, after one cup of champagne is poured, the top most glass is full. After two cups of champagne are poured, the two glasses on  the second row are half full. After three cups of champagne are poured, those two cups become full - there are 3 full glasses total now. After four cups of champagne are poured, the third row has the middle glass  half full, and the two outside glasses are a quarter full, as pictured  below.

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/03/09/tower.png)

Now after pouring some non-negative integer cups of champagne, return how full the `jth` glass in the `ith` row is (both `i` and `j` are 0-indexed.)

 

**Example 1:**

```
Input: poured = 1, query_row = 1, query_glass = 1
Output: 0.00000
Explanation: We poured 1 cup of champange to the top glass of the tower (which is indexed as (0, 0)). There will be no excess liquid so all the glasses under the top glass will remain empty.
```

**Example 2:**

```
Input: poured = 2, query_row = 1, query_glass = 1
Output: 0.50000
Explanation: We poured 2 cups of champange to the top glass of the tower (which is indexed as (0, 0)). There is one cup of excess liquid. The glass indexed as (1, 0) and the glass indexed as (1, 1) will share the excess liquid equally, and each will get half cup of champange.
```

**Example 3:**

```
Input: poured = 100000009, query_row = 33, query_glass = 17
Output: 1.00000
```

 

**Constraints:**

- `0 <= poured <= 109`
- `0 <= query_glass <= query_row < 100`

## 题目大意

我们把玻璃杯摆成金字塔的形状，其中 *第一层* 有 `1` 个玻璃杯， 第二层 有 `2` 个，依次类推到第 `100` 层，每个玻璃杯 `(250ml)` 将盛有香槟

从顶层的第一个玻璃杯开始倾倒一些香槟，当顶层的杯子满了，任何溢出的香槟都会立刻等流量的流向左右两侧的玻璃杯。当左右两边的杯子也满了，就会等流量的流向它们左右两边的杯子，依次类推。（当最底层的玻璃杯满了，香槟会流到地板上）

例如，在倾倒一杯香槟后，最顶层的玻璃杯满了。倾倒了两杯香槟后，第二层的两个玻璃杯各自盛放一半的香槟。在倒三杯香槟后，第二层的香槟满了 - 此时总共有三个满的玻璃杯。在倒第四杯后，第三层中间的玻璃杯盛放了一半的香槟，他两边的玻璃杯各自盛放了四分之一的香槟，如下图所示。

现在当倾倒了非负整数杯香槟后，返回第 `i` 行 `j` 个玻璃杯所盛放的香槟占玻璃杯容积的比例（ `i` 和 `j` 都从0开始）

## 解题思路


### Solution 1: DP

状态定义为 `dp[i][j]` 表示 `dp[i][j]` 的比例，


在整个状态转移过程中，如果当前 杯子已满(`dp[i][j] > 1`):

- `dp[i + 1][j] = (dp[i][j] - 1) / 2`
- `dp[i + 1][j + 1] = (dp[i][j] - 1) / 2`

根据状态转移方程，不难得出，初始化需要将 `dp[0][0] = poured`

可以参考 [这篇题解](https://leetcode.cn/problems/champagne-tower/solution/xiang-bin-ta-dong-tai-gui-hua-by-yuer-fl-f7uc/)


````c++
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>> dp(query_row + 1, vector<double>(query_row+ 1));
        dp[0][0] = poured;
        for (int i = 0; i < query_row; ++i) {
            for (int j = 0; j <= i; ++j) {
                if (dp[i][j] > 1) {
                    double diff = (dp[i][j] - 1) / 2;
                    dp[i + 1][j] += diff;
                    dp[i + 1][j + 1] += diff;
                }
            }
        }

        return min(1.0, dp[query_row][query_glass]);
    }
};
````



