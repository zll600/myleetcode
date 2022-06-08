# [926. Flip String to Monotone Increasing](https://leetcode.cn/problems/flip-string-to-monotone-increasing/)

## 题目

A binary string is monotone increasing if it consists of some number of `0`'s (possibly none), followed by some number of `1`'s (also possibly none).

You are given a binary string `s`. You can flip `s[i]` changing it from `0` to `1` or from `1` to `0`.

Return *the minimum number of flips to make* `s` *monotone increasing*.

 

**Example 1:**

```
Input: s = "00110"
Output: 1
Explanation: We flip the last digit to get 00111.
```

**Example 2:**

```
Input: s = "010110"
Output: 2
Explanation: We flip to get 011111, or alternatively 000111.
```

**Example 3:**

```
Input: s = "00011000"
Output: 2
Explanation: We flip to get 00000000.
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is either `'0'` or `'1'`.

## 题目大意

给你一个二进制字符串 `s`，你可以将任何 `0` 翻转为 `1` 或者将 `1` 翻转为 `0` 。

返回使 `s` 单调递增的最小翻转次数

## 解题思路

定义状态为在满足递增的前提下，`dp[i][0]` 表示第 i 位置为 0 的最小翻转次数，`dp[i][1]` 表示第 i 个位置为 1 的最小反转次数

状态转移方程为

- `dp[i][0] = dp[i - 1][0] + (s[i] == '0' ? 0 : 1)`，
- `dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + (s[i] == '0' ? 0 : 1)` 因为要使得第 i 个位置为 0，那么前 i - 1 个位置必须均为 0，如果要使得第 i 个位置为 1，没有要求

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/flip-string-to-monotone-increasing/solution/zui-gui-fan-de-dong-tai-gui-hua-xie-fa-d-82le/)

````c++
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        const int len = s.size();
        vector<vector<int>> dp(len, vector<int>(2));


        dp[0][0] = s[0] == '0' ? 0 : 1;
        dp[0][1] = s[0] == '1' ? 0 : 1;
        for (int i = 1; i < len; ++i) {
            // 若第 i 个位置为 0，那么前 i 个位置都必须为 0
            dp[i][0] = dp[i - 1][0] + (s[i] == '0' ? 0 : 1);
            // 若要使第 i 个位置为 1，只需要第 i 个位置为 1，前面没有影响
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0]) + (s[i] == '1' ? 0 : 1);
        }

        return min(dp[len - 1][0], dp[len - 1][1]);
    }
};
````
