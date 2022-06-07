#### [861. Score After Flipping Matrix](https://leetcode.cn/problems/score-after-flipping-matrix/)

You are given an `m x n` binary matrix `grid`.

A **move** consists of choosing any row or column and toggling each value in that row or column (i.e., changing all `0`'s to `1`'s, and all `1`'s to `0`'s).

Every row of the matrix is interpreted as a binary number, and the **score** of the matrix is the sum of these numbers.

Return *the highest possible **score** after making any number of **moves** (including zero moves)*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/07/23/lc-toogle1.jpg)

```
Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
```

**Example 2:**

```
Input: grid = [[0]]
Output: 1
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 20`
- `grid[i][j]` is either `0` or `1`.

## 题目大意

有一个二维矩阵 A 其中每个元素的值为 0 或 1 。

移动是指选择任一行或列，并转换该行或列中的每一个值：将所有 0 都更改为 1，将所有 1 都更改为 0。

在做出任意次数的移动后，将该矩阵的每一行都按照二进制数来解释，矩阵的得分就是这些数字的总和。

返回尽可能高的分数


## 解题思路

这道题目还是比较容易想起使用贪心来做的，

这里不难发现，高位的 1 对最终结果的贡献肯定是最大的，所以尽可能要使得高位为 1，

- 如果高位不是 1，那就翻转整行
- 如果高位是 1，那就不翻转

对于没一列，产生尽可能多的 1

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/score-after-flipping-matrix/solution/fan-zhuan-ju-zhen-tan-xin-xin-lu-li-chen-21h7/)

````c++
class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        const int rows = grid.size();
        const int cols = grid[0].size();

        // 每一行的高位尽可能为 1
        for (int i = 0; i < rows; ++i) {
            if (grid[i][0] == 1) {
                continue;
            }

            for (int j = 0; j < cols; ++j) {
                grid[i][j] ^= 1;
            }
        }

        // 每一列尽可能多的出现 1
        int scores = 0;
        for (int j = 0; j < cols; ++j) {
            int cnt = 0;
            for (int i = 0; i < rows; ++i) {
                cnt += grid[i][j];
            }
            scores += max(cnt, rows - cnt) * (1 << (cols - j - 1));
        }
        return scores;
    }
};
````
