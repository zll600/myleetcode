# [474. Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/)

## 题目

You are given an array of binary strings `strs` and two integers `m` and `n`.

Return *the size of the largest subset of `strs` such that there are **at most*** `m` `0`*'s and* `n` `1`*'s in the subset*.

A set `x` is a **subset** of a set `y` if all elements of `x` are also elements of `y`.

 

**Example 1:**

```
Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
```

**Example 2:**

```
Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.
```

 

**Constraints:**

- `1 <= strs.length <= 600`
- `1 <= strs[i].length <= 100`
- `strs[i]` consists only of digits `'0'` and `'1'`.
- `1 <= m, n <= 100`

## 题目大意

给定一个二进制的数组 strs，和两个整数 m 和 n，返回能够在子集中出现 m 和 0 和 n 个 1 的最大子集数，

## 解题思路

* 这是一道 DP 01 背包的题目，
* 这里需要建立一个三维的数组，状态的定义：`dp[i][j][k]`表示输入字符串在子区间 [0, i]，能够使用 j 个0 和 k 个1 的字符串的最大数量，
* 状态转移方程 `dp[i][j][k] = dp[i - 1][j][k] 不选 或者是 dp[i - 1][j - 当前字符串的 0 的数目][k - 当前字符串的 1 的数目] + 1 选`
* 初始化的时候，为了避免分类讨论，通常多设置一行，这里可以认为第0 个字符串使空串，第 0 行默认初始化为 0，
* 输出为 `dp[size][m][n]`

## 代码

```c++
class Solution {
public:    
    int findMaxForm1(vector<string>& strs, int m, int n) {
        int size = strs.size();

        vector<pair<int, int>> cache = Preprocess(strs);
        /*
        vector<vector<vector<int>>> dp(size, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (i >= cache[0].first && j >= cache[0].second) {
                    dp[0][i][j] = 1;
                }
            }   
        }

        for (int i = 1; i < size; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int k = 0; k <= n; ++k) {
                    dp[i][j][k] = dp[i - 1][j][k];

                    if (j >= cache[i].first && k >= cache[i].second) {
                        dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - cache[i].first][k - cache[i].second] + 1);
                    }
                }
            }
        }
        return dp[size - 1][m][n];
        */
        
        // 这里利用一个哨兵值来避免分类讨论，帮助递推过程
        vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        for (int i = 1; i <= size; ++i) {
            for (int j = 0; j <= m; ++j) {
                for (int k = 0; k <= n; ++k) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    
                    if (j >= cache[i - 1].first && k >= cache[i - 1].second) {
                        dp[i][j][k] = max(dp[i][j][k],
                                          dp[i - 1][j - cache[i - 1].first][k - cache[i - 1].second] + 1);
                    }
                }
            }
        }
        return dp[size][m][n];
    }
    
    // 利用滚动数组进行优化
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<pair<int, int>> cache = Preprocess(strs);
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 0; i < strs.size(); ++i) {
            for (int j = m; j >= cache[i].first; --j) {
                for (int k = n; k >= cache[i].second; --k) {
                    dp[j][k] = max(dp[j][k], dp[j - cache[i].first][k - cache[i].second] + 1);
                }
            }
        }
        
        return dp[m][n];
    }

 private:
    vector<pair<int, int>> Preprocess(const vector<string>& strs) {
        int size = strs.size();
        vector<pair<int, int>> cache;

        for (const string& str : strs) {
            cache.push_back(Calc(str));
        }
        return cache;
    }

    pair<int, int> Calc(const string& str) {
        int ones = 0;
        int zeros = 0;

        for (const char c : str) {
            if (c == '1') {
                ++ones;
            } else {
                ++zeros;
            }
        }

        return make_pair(zeros, ones);
    }
};
```

