# [91. Decode Ways](https://leetcode.com/problems/decode-ways/)

## 题目

A message containing letters from `A-Z` can be **encoded** into numbers using the following mapping:

```
'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
```

To **decode** an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, `"11106"` can be mapped into:

- `"AAJF"` with the grouping `(1 1 10 6)`
- `"KJF"` with the grouping `(11 10 6)`

Note that the grouping `(1 11 06)` is invalid because `"06"` cannot be mapped into `'F'` since `"6"` is different from `"06"`.

Given a string `s` containing only digits, return *the **number** of ways to **decode** it*.

The answer is guaranteed to fit in a **32-bit** integer.

 

**Example 1:**

```
Input: s = "12"
Output: 2
Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
```

**Example 2:**

```
Input: s = "226"
Output: 3
Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
```

**Example 3:**

```
Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with 0.
The only valid mappings with 0 are 'J' -> "10" and 'T' -> "20", neither of which start with 0.
Hence, there are no valid ways to decode this since all digits need to be mapped.
```

**Example 4:**

```
Input: s = "06"
Output: 0
Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06").
```

 

**Constraints:**

- `1 <= s.length <= 100`
- `s` contains only digits and may contain leading zero(s).

## 题目大意

一条包含字母(A-Z)的消息，可以按照如下关系进行编码：

````
'A' -> "1"
'B' -> "2"
...
'Z' -> "26"
````

返回解码一个字符串的方法数

## 解题思路

* 这是一道 线性 DP 问题，对于字符串的某个位置而言，我们只关心 i 位置的字符能否独立解码，和 i 位置的字符能否和i - 1 位置的字符一起解码，而不用关心 i - 1之前的位置
* 状态定义：`dp[i]`表示考虑前  i  个字符的解码方案数，
* 状态转移：
  * 只能有 i 位置字符单独解码，转移的前提是 i 位置字符的范围为 [1, 9]，`dp[i] = dp[i - 1]`
  * 只能由位置 i 的前一个位置 I - 1 共同作为一个单位进行解码，转移的前提是这个单位的范围是 [10, 26] `dp[i] = dp[i - 1]`
  * 位置 i 既能独立解码也可以和前一个数字作为一个单位进行解码，`dp[i] = dp[i - 1] + dp[i - 2]`
* 初始化：这里依旧采用空一格来避免分类讨论，并且使状态可以转移

## 代码

````c++
class Solution {
public:
    int numDecodings1(string s) {
        int len = s.size();
        vector<int> dp(len + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= len; ++i) {
            int cur = s[i - 1] - '0';
            int prev = i - 2 >= 0 ? s[i - 2] - '0' : INT_MIN;
            
            // 当前位置可以独立进行状态转移
            if (cur >= 1 && cur <= 9) {
                dp[i] = dp[i - 1];
            }
            
            // 当前位置可以与前一个位置一起进行状态转移
            if (prev != INT_MIN) {
                int item = prev * 10 + cur;
                if (item >= 10 && item <= 26) {
                    dp[i] += dp[i - 2];
                }
            }
        }
        
        return dp[len];
    }
    
    // 空间优化，状态转移之涉及 i, i - 1, i - 2
    // 用有限的变量来进行状态转移
    int numDecodings(string s) {
        int len = s.size();
        
        int first =  1;
        int second = 0;
        
        for (int i = 0; i < len; ++i) {
            int cur = s[i] - '0';
            int prev = i - 1 >= 0 ? s[i - 1] - '0' : INT_MIN;
            
            int tmp = 0;
            if (cur >= 1 && cur <= 9) {
                tmp = first;
            }
            
            if (prev != INT_MIN) {
                int item = prev * 10 + cur;
                if (item >= 10 && item <= 26) {
                    tmp += second;
                }
            }
            second = first;
            first = tmp;
        }
        
        return first;
    }
};
````

