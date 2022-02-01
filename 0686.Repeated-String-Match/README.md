# [686. Repeated String Match](https://leetcode-cn.com/problems/repeated-string-match/)

## 题目

Given two strings `a` and `b`, return *the minimum number of times you should repeat string* `a` *so that string* `b` *is a substring of it*. If it is impossible for `b` to be a substring of `a` after repeating it, return `-1`.

**Notice:** string `"abc"` repeated 0 times is `""`, repeated 1 time is `"abc"` and repeated 2 times is `"abcabc"`.

 

**Example 1:**

```
Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
```

**Example 2:**

```
Input: a = "a", b = "aa"
Output: 2
```

 

**Constraints:**

- `1 <= a.length, b.length <= 104`
- `a` and `b` consist of lowercase English letters.

## 题目大意

给定两个字符串 `a` 和 `b`，返回能使字符串 `b` 成为字符串 `a` 的子串的最小的使字符串 `a` 重复的次数，如果不可能，返回 -1

**注意**：字符串 `abc` 重复 0 次得到 `""`，重复一次得到 `"abc"`，重复两次得到 `"abcabc"`


## 解题思路

这里要解决的问题有：
* 字符串 `a` 重复后拼接的字符串，长度一定大于等于 `b`，
* 拼接后的字符串中是否存在 `b`，


### Solution 1:

这种解法采用的思路就是先重复字符串 `a` 直到字符串的长度大于等于 b 的长度，此时再额外加上一个 `a`，保证可以找到 `b`，查找使用的是stl 的 find 函数

另外这里的结果要 +1 ，题目要求至少重复一次


````c++
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        string str = a;
        while (str.size() < b.size()) {
            // 重复直到长度符合条件
            str += a;
        }
        str += a;
        
        const int found = str.find(b);
        if (found == string::npos) {
            return -1;
        }
        
        // 这里 +1 是因为至少要重复一次，
        return (found + b.size() - 1) / a.size() + 1;
    }
};

````
