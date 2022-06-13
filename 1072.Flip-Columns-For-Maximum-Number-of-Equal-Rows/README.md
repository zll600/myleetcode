# [1072. Flip Columns For Maximum Number of Equal Rows](https://leetcode.cn/problems/flip-columns-for-maximum-number-of-equal-rows/)

## 题目

You are given an `m x n` binary matrix `matrix`.

You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from `0` to `1` or vice versa).

Return *the maximum number of rows that have all values equal after some number of flips*.

 

**Example 1:**

```
Input: matrix = [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.
```

**Example 2:**

```
Input: matrix = [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.
```

**Example 3:**

```
Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.
```

 

**Constraints:**

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 300`
- `matrix[i][j]` is either `0` or `1`.

## 题目大意

给定 `m x n` 矩阵 `matrix`

你可以从中选出任意数量的列并翻转其上的 *每个* 单元格。（即翻转后，单元格的值从 `0` 变成 `1`，或者从 `1` 变为 `0` ）

返回 经过一些翻转后，行与行之间所有值都相等的最大行数

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/flip-columns-for-maximum-number-of-equal-rows/solution/xun-zhao-ju-you-xiang-tong-de-te-zheng-de-xing-de-/)

观察: 

010 ^ 101 = 111

110 ^ 001 = 111

可以发现如果两行做异或运算，如果所有位置上都可以是 1，，那么就可以使得这两行的每个位置都相等

我们假设有两行 a b,那么有 a ^ b = c ，若 c 为全 1，那么 a ^ c = b，所以可以将所有行分为两类，

以 0 开头的，直接加入 map 中参与计数，以 1 开头，和全 1 做异或，那么得到的就是可以与其配对的那一行，参与计数，这里就相当于 x 2了

````c++
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        const int m = matrix.size();
        const int n = matrix[0].size();
        unordered_map<string, int> freq;
        
        int res = 0;
        for (int i = 0; i < m; ++i) {
            bool first_zero = false;
            if (matrix[i][0] == 0) {
                first_zero = true;
            }
            
            string tmp;
            for (int j = 0; j < n; ++j) {
                if (first_zero) {
                    tmp.append(1, matrix[i][j] + '0');
                } else {
                    tmp.append(1, (matrix[i][j] ^ 1) + '0');
                }
            }
            ++freq[tmp];
            res = max(res, freq[tmp]);
        }
        
        return res;
    }
};
````
