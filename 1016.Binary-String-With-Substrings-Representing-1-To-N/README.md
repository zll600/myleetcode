# [1016. Binary String With Substrings Representing 1 To N](https://leetcode.cn/problems/binary-string-with-substrings-representing-1-to-n/)

##  题目

Given a binary string `s` and a positive integer `n`, return `true` *if the binary representation of all the integers in the range* `[1, n]` *are **substrings** of* `s`*, or* `false` *otherwise*.

A **substring** is a contiguous sequence of characters within a string.

 

**Example 1:**

```
Input: s = "0110", n = 3
Output: true
```

**Example 2:**

```
Input: s = "0110", n = 4
Output: false
```

 

**Constraints:**

- `1 <= s.length <= 1000`
- `s[i]` is either `'0'` or `'1'`.
- `1 <= n <= 109`

## 题目大意

给定一个二进制字符串 `s` 和一个正整数 `n`，如果对于 `[1, n]` 范围内的每个整数，其二进制表示都是 `s` 的 子字符串 ，就返回 `true`，否则返回 `false`

子字符串 是字符串中连续的字符序列

## 解题思路


### Solution 1:

这道题目简单模拟一下就可以了，直接暴力解法就可以通过，

这里需要注意的是，遍历所有的子串可能的值，会包含 0，在最终计数时，或者在遍历时必须除去 0

````c++
class Solution {
public:
    bool queryString(string s, int n) {
        unordered_set<int> nums;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') {
                continue;
            }
            int cur = 0;
            for (int j = i; j < s.size(); ++j) {
                cur = (cur << 1) + s[j] - '0';
                if (cur > n) {
                    break;
                }
                nums.emplace(cur);
            }
        }

        // for (int cur : nums) {
        //     cout << cur << endl;
        // }
        // nums.erase(0);

        return nums.size() == n;
    }
};
````
