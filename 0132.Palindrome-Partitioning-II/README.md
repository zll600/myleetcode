# [132. Palindrome Partitioning II](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)

## 题目

Given a string `s`, partition `s` such that every substring of the partition is a palindrome.

Return *the minimum cuts needed* for a palindrome partitioning of `s`.

 

**Example 1:**

```
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
```

**Example 2:**

```
Input: s = "a"
Output: 0
```

**Example 3:**

```
Input: s = "ab"
Output: 1
```

 

**Constraints:**

- `1 <= s.length <= 2000`
- `s` consists of lower-case English letters only.

## 题目大意

给定一个字符串 s，分割s，使得s的每个部分都是回文的，返回使得 s 的每一个部分都是回文的最小分割数

## 解题思路

这道题目由两部分组成，我们需要判断分割出的子串是否符合回文的条件，还要判断分割字符串的最小切割数

### Solution 1:

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/palindrome-partitioning-ii/solution/xiang-jie-liang-bian-dong-tai-gui-hua-ji-s5xr/

这道题目如果分成两次动态规划来做的话，就没有那么难，但是状态转移方程还是不太好想，

另外，我觉得，这里的递推过程，有一个部分可以放在初始化的过程中，这样递推过程中，可以减少分支判断

````c++
class Solution {
public:
    int minCut(string s) {
        const int len = s.size();
        // 这里是预处理，利用递推提前判断好所有的回文串
        // 状态定义 cache[left][right] 表示 [left - 1, right - 1] 的子串的是否为回文串
        // 这里利用了哨兵的思想，来避免分类讨论
        vector<vector<bool>> cache(len + 1, vector<bool>(len + 1, false));
        for (int right = 1; right <= len; ++right) {
            for (int left = right; left >= 1; --left) {
                if (left == right) {
                    // 如果子串的长度为 1（这里也可以放在初始化里面做）
                    cache[left][right] = true;
                } else {
                    // 这里才是真的状态转移
                    // 如果两个字符相同，
                    // 1.如果子串的长度为 2，
                    // 2.如果包含的子串也是回文串
                    if (s[left - 1] == s[right - 1]) {
                        if (right - left == 1 || cache[left + 1][right - 1]) {
                            cache[left][right] = true;
                        }
                    }
                }
            }
        }
        
        // 状态定义：dp[right] 表示从 前 right 个字符组成的子串需要的最少分割数
        vector<int> dp(len + 1, 0);
        for (int right = 1; right <= len; ++right) {
            // 状态转移
            if (cache[1][right]) {
                // 如果前 right 个字符本身就是回文子串，
                dp[right] = 0;
            } else {
                // 否则，需要枚举分割点，选择最小的分割数
                dp[right] = right - 1; // 前 right 个字符，最多需要right - 1次切割
                for (int left = 1; left <= right; ++left) {
                    if (cache[left][right]) {
                        dp[right] = min(dp[right], dp[left - 1] + 1);
                    }
                }
            }
        }
        
        return dp[len];
    }
};
````

