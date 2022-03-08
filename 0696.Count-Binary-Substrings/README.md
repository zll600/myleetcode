# [696. Count Binary Substrings](https://leetcode.com/problems/count-binary-substrings/)

## 题目

Give a binary string `s`, return the number of non-empty substrings that have the same number of `0`'s and `1`'s, and all the `0`'s and all the `1`'s in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

 

**Example 1:**

```
Input: s = "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
Notice that some of these substrings repeat and are counted the number of times they occur.
Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
```

**Example 2:**

```
Input: s = "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is either `'0'` or `'1'`.

## 题目大意

返回含有相同数量的 `'1'` 和 `'0'`，且 `'1'` 和 `'0'` 均是连续存在的非空子串的数量

重复出现的字符串要计算他们的数量

## 解题思路

首先可以想到，这道题目肯定是可以用暴力法来解决的，但是这里涉及到的是子串问题，所以必须连续 

### Solution 1:

这种解法可以参考霜神的 [题解](https://books.halfrost.com/leetcode/ChapterFour/0600~0699/0696.Count-Binary-Substrings/#%e8%a7%a3%e9%a2%98%e6%80%9d%e8%b7%af)

具体做法就是分别同意连续的 0 和 1 的个数，并选取其中最小的，就是可以选取相同的数目了

````c++
class Solution {
public:
    int countBinarySubstrings(string s) {
        // 上一种字符连续出现的次数
        int last = 0;

        const int len = s.size();
        int res = 0;
        int i = 0;
        while (i < len) {
            // 统计当前字符出现的次数
            int cnt = 1;
            char c = s[i];
            for (++i; i < len && s[i] == c; ++i) {
                ++cnt;
            }
            // 这里选取最小的，就是可以形成的符合条件的子串的书目
            // 这里加速了统计
            // "00111" --> "0011", "01" 是两个
            res += min(cnt, last);
            last = cnt;
        }

        return res;
    }
};
````
