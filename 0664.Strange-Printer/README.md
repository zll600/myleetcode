# [664. Strange Printer](https://leetcode-cn.com/problems/strange-printer/)

## 题目

There is a strange printer with the following two special properties:

- The printer can only print a sequence of **the same character** each time.
- At each turn, the printer can print new characters starting from and ending at any place and will cover the original existing characters.

Given a string `s`, return *the minimum number of turns the printer needed to print it*.

 

**Example 1:**

```
Input: s = "aaabbb"
Output: 2
Explanation: Print "aaa" first and then print "bbb".
```

**Example 2:**

```
Input: s = "aba"
Output: 2
Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.
```

 

**Constraints:**

- `1 <= s.length <= 100`
- `s` consists of lowercase English letters.

## 题目大意

有一个有两个特殊属性的打印机：

* 打印机一次只能打印同样的字母
* 每次可以在从起始到结束的任意位置打印新字符，并且会覆盖掉原来已有的字符

给定一个字符串 s，返回打印机需要打印的最小次数

## 解题思路

这道题目也是一道区间dp 的题目，可以参考这篇题解：https://leetcode-cn.com/problems/strange-printer/solution/xin-shou-pian-cong-xiao-wen-ti-zai-dao-q-qifh/

### Solution 1:

这道题的状态转移方程是根据规律推出来的，所以并不好写



````c++
class Solution {
public:
    int strangePrinter(string s) {
        const int len = s.size();
        // 状态定义：dp[i][k] 表示 [i...j] 范围内最小打印次数
        vector<vector<int>> dp(len, vector<int>(len, INT_MAX));
        // 初始化
        for (int i = 0; i < len; ++i) {
            dp[i][i] = 1;
        }
        
        for (int i = len - 2; i >= 0; --i) {
            for (int j = i + 1; j < len; ++j) {
                // 递推公式
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i][j - 1];
                } else {
                    for (int k = i; k < j; ++k) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                    }
                }
            }
        }
        
        return dp[0][len - 1];
    }
};
````

