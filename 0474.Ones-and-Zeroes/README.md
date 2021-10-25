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

这道题目可以参考这两篇题解：https://leetcode-cn.com/problems/ones-and-zeroes/solution/dong-tai-gui-hua-zhuan-huan-wei-0-1-bei-bao-wen-ti/

https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0474.Ones-and-Zeroes/

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

### Solution 1: DFS(TLE)

使用 DFS 来解决，状态的改变有三个量，数组下表，0 的数目， 1 的数目

`````c++
class Solution {
 public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        return DFS(strs, 0, 0, m, n);
    }

private:
    int DFS(const vector<string>& strs, int idx, int cnt,
            int m, int n) {
        if (m < 0 || n < 0) {
            return cnt - 1;
        }

        if (idx == strs.size()) {
            return cnt;
        }

        int ones = 0, zeros = 0;
        for (char c : strs[idx]) {
            if (c == '1') {
                ++ones;
            } else {
                ++zeros;
            }
        }

        return max(DFS(strs, idx + 1, cnt + 1, m - zeros, n - ones),
                    DFS(strs, idx + 1, cnt, m, n));
    }
};
`````

### Solution 2: DSF + 记忆化(TLE)

````c++
class Solution {
 public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        unordered_map<string, int> cache;
        return DFS(strs, 0, 0, m, n, cache);
    }

private:
    int DFS(const vector<string>& strs, int idx, int cnt,
            int m, int n, unordered_map<string, int>& cache) {
        if (m < 0 || n < 0) {
            return cnt - 1;
        }

        if (idx == strs.size()) {
            return cnt;
        }

        string key = to_string(idx) + '-' + to_string(cnt) + '-'
                    + to_string(m) + '-' + to_string(n);
        if (cache.find(key) != cache.end()) {
            return cache.at(key);
        }

        int ones = 0, zeros = 0;
        for (char c : strs[idx]) {
            if (c == '1') {
                ++ones;
            } else {
                ++zeros;
            }
        }

        int res =  max(DFS(strs, idx + 1, cnt + 1, m - zeros, n - ones, cache),
                    DFS(strs, idx + 1, cnt, m, n, cache));
        cache[key] = res;
        return res;
    }
};
````

### Solution : DP

`````c++
class Solution {
 public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        const int size = strs.size();
        // dp[i][j][k] 表示 [0, i) 范围内的元素构成 j个0，k个1
        vector<vector<vector<int>>> dp(size + 1,
                                        vector<vector<int>>(m + 1, vector<int>(n + 1)));
        // 状态转移
        for (int i = 1; i < size + 1; ++i) {
            // 取得 0 和 1 的个数
            pair<int, int> cnt = Calc(strs[i - 1]);
            for (int j = 0; j < m + 1; ++j) {
                for (int k = 0; k < n + 1; ++k) {
                    // 先继承上一层，
                    dp[i][j][k] = dp[i - 1][j][k];
                    // 更新去最大
                    if (j >= cnt.first && k >= cnt.second) {
                        dp[i][j][k] = max(dp[i][j][k],
                                dp[i - 1][j - cnt.first][k - cnt.second] + 1);
                    }
                }
            }
        }

        return dp[size][m][n];
    }

 private:
    pair<int, int> Calc(const string& str) {
        int zeros = 0, ones = 0;
        for (char c : str) {
            if (c == '1') {
                ++ones;
            } else {
                ++zeros;
            }
        }

        return pair<int, int>(zeros, ones);
    }
};
`````

### Solution 1: dp + 空间优化

关于这里为什么要从后向前算，这里可以现写三维，然后向二维优化，就会发现，因为这里层，只用到上一层的值，如果从前向后更新，则还需要保存修改之前的值

````c++
class Solution {
 public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        // dp[i][j] 表示可以组成 i 个0 和 j 个 1 的最大元素数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        // 遍历所有的字符串
        for (const string& str : strs) {
            // 取得 0 和 1 的个数
            pair<int, int> cnt = Calc(str);
            // 如果不满足条件，直接返回
            if (cnt.first > m || cnt.second > n) {
                continue;
            }
            // 状态转移，这里从后向前算，可以避免复制数组
            for (int i = m; i >= cnt.first; --i) {
                for (int j = n; j >= cnt.second; --j) {
                    dp[i][j] = max(dp[i][j], dp[i - cnt.first][j - cnt.second] + 1);
                }
            }
        }

        return dp[m][n];
    }

 private:
    pair<int, int> Calc(const string& str) {
        int zeros = 0, ones = 0;
        for (char c : str) {
            if (c == '1') {
                ++ones;
            } else {
                ++zeros;
            }
        }

        return pair<int, int>(zeros, ones);
    }
};
````

