# [1641. Count Sorted Vowel Strings](https://leetcode-cn.com/problems/count-sorted-vowel-strings/)

## 题目

Given an integer `n`, return *the number of strings of length* `n` *that consist only of vowels (*`a`*,* `e`*,* `i`*,* `o`*,* `u`*) and are **lexicographically sorted**.*

A string `s` is **lexicographically sorted** if for all valid `i`, `s[i]` is the same as or comes before `s[i+1]` in the alphabet.

 

**Example 1:**

```
Input: n = 1
Output: 5
Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
```

**Example 2:**

```
Input: n = 2
Output: 15
Explanation: The 15 sorted strings that consist of vowels only are
["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
Note that "ea" is not a valid string since 'e' comes after 'a' in the alphabet.
```

**Example 3:**

```
Input: n = 33
Output: 66045
```

 

**Constraints:**

- `1 <= n <= 50` 

## 题目大意

返回长度为 `n` 的只包含元音字符且按照字典序排序的字符串的数目

## 解题思路

这道题目也是计数DP 的一种

一开始定义的状态是 `dp[i][j]` 表示长度为 `i`，使用前 `j` 个字符的字符串的数目，但是这样的话，状态转移方程不太好写，

### Solution 1: DP

这道题目艰难的写出来了，

这里除了第一行的其他行都是由上方和左方递推过来的，可以这样理解

长度为 1 ，['a', 'e', 'i', 'o', 'u']，长度为 2，以 'u' 开头的就是 'u'，以 'o'，开头的有 'ou'，'oo'，应该是数学中的组合知识，

也可以参考 [这篇题解](https://leetcode-cn.com/problems/count-sorted-vowel-strings/solution/tui-li-gui-lu-dong-tai-gui-hua-by-limbo-pby29/)

````c++
class Solution {
 public:
    int countVowelStrings(int n) {
        // dp[i][j] 表示长度为 i，以 vowels_[j] 开头的字符串的数目
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));
        
        // 上面初始化所有元素为 1，
        for (int i = 0; i < 5; ++i) {
            dp[1][i] = 1;
        }
        
        // 进行递推
        for (int i = 2; i <= n; ++i) {
            dp[i][4] = dp[i - 1][4];
            for (int j = 3; j >= 0; --j) {
                dp[i][j] = dp[i][j + 1] + dp[i - 1][j];
            }
        }
        
        return ::accumulate(dp[n].begin(), dp[n].end(), 0);
    }
};
````
