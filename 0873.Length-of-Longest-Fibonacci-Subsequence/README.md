# [873. Length of Longest Fibonacci Subsequence](https://leetcode.cn/problems/length-of-longest-fibonacci-subsequence/)

## 题目

A sequence `x1, x2, ..., xn` is *Fibonacci-like* if:

- `n >= 3`
- `xi + xi+1 == xi+2` for all `i + 2 <= n`

Given a **strictly increasing** array `arr` of positive integers forming a sequence, return *the **length** of the longest Fibonacci-like subsequence of* `arr`. If one does not exist, return `0`.

A **subsequence** is derived from another sequence `arr` by deleting any number of elements (including none) from `arr`, without changing the order of the remaining elements. For example, `[3, 5, 8]` is a subsequence of `[3, 4, 5, 6, 7, 8]`.

 

**Example 1:**

```
Input: arr = [1,2,3,4,5,6,7,8]
Output: 5
Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].
```

**Example 2:**

```
Input: arr = [1,3,7,11,12,14,18]
Output: 3
Explanation: The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or [7,11,18].
```

 

**Constraints:**

- `3 <= arr.length <= 1000`
- `1 <= arr[i] < arr[i + 1] <= 109`

## 题目大意

如果序列 `X_1, X_2, ..., X_n` 满足下列条件，就说它是 *斐波那契式* 的：

-  `n >= 3`
-   对于所有 `i + 2 <= n`，都有 `X_i + X_{i+1} = X_{i+2}`

给定一个严格递增的正整数数组形成序列 `arr` ，找到 `arr` 中最长的斐波那契式的子序列的长度。如果一个不存在，返回  `0`

（回想一下，子序列是从原序列 `arr` 中派生出来的，它从 `arr` 中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， `[3, 5, 8]` 是 `[3, 4, 5, 6, 7, 8]` 的一个子序列）

## 解题思路

这道题目还是比较容易想到使用 dp 的，

这里的状态定义是 `dp[i][j]` 表示 [i...j] 的诶波那契式子序列的长度

状态转移方程是: 

假设存在 arr[i] 之前存在一个数 arr[k]，满足 `arr[k] + arr[i] == arr[j]`，那么 `dp[i][j] = max(dp[i][j], dp[k][i] + 1)`

这里不难想到要求出 `dp[i][j]`，必须找到 `arr[k]`，这里会想到遍历，下面的解法中在这里做了优化，保存一个arr 中 value -> index 的映射，降低查找复杂度

根据这里的状态方程进行初始化，初始化所有的二元组

### Solution 1: DP

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/length-of-longest-fibonacci-subsequence/solution/zhuang-tai-ding-yi-hen-shi-zhong-yao-by-christmas_/)

````c++
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        const int len = arr.size();
        vector<vector<int>> dp(len, vector<int>(len));
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                dp[i][j] = 2;
            }
        }

        unordered_map<int, int> relat;
        for (int i = 0; i < len; ++i) {
            relat.emplace(arr[i], i);
        }

        int ans = 0;
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                int diff = arr[j] - arr[i];

                auto it = relat.find(diff);
                if (it != relat.end() && it->second < i) {
                    dp[i][j] = max(dp[i][j], dp[it->second][i] + 1);
                }
                ans = max(ans, dp[i][j]);
            }
        }
        return ans >= 3 ? ans : 0;
    }
};
````

