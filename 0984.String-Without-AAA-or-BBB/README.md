# [984. String Without AAA or BBB](https://leetcode.com/problems/string-without-aaa-or-bbb/)

## 题目

Given two integers `a` and `b`, return **any** string `s` such that:

- `s` has length `a + b` and contains exactly `a` `'a'` letters, and exactly `b` `'b'` letters,
- The substring `'aaa'` does not occur in `s`, and
- The substring `'bbb'` does not occur in `s`.

 

**Example 1:**

```
Input: a = 1, b = 2
Output: "abb"
Explanation: "abb", "bab" and "bba" are all correct answers.
```

**Example 2:**

```
Input: a = 4, b = 1
Output: "aabaa"
```

 

**Constraints:**

- `0 <= a, b <= 100`
- It is guaranteed such an `s` exists for the given `a` and `b`.

## 题目大意

给定两个整数 `A` 和 `B`，返回任意字符串 `S`，要求满足：

- `S` 的长度为 `A + B`，且正好包含 `A` 个 `‘a’` 字母与 `B` 个 `‘b’` 字母；
- 子串 `‘aaa’` 没有出现在 `S` 中；
- 子串 `‘bbb’` 没有出现在 `S` 中。

## 解题思路

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/string-without-aaa-or-bbb/solution/984-c-jian-dan-tan-xin-de-zi-fu-chuan-chu-li-by-sm/)

这里我们这样考虑，

- 首先追加剩余数目较大的字符，且该字符已经连续出现的数目必须小于 2
- 然后考虑当剩余数目较大的字符出现次数等于 2 时，必须追加另一种字符

````c++
class Solution {
public:
    string strWithout3a3b(int a, int b) {
        string res = "";
        int len = a + b;
        int con_a = 0, con_b = 0;
        while (res.size() < len) {
            // 在追加字符的时候
            // 1、追加剩余数量较大的字符，且这个字符的已经出现的连续的数目不能超过 2
            // 2、如果已经连续出现 2 次，必须追加另一种字符
            if ((a > b && con_a < 2)
                || (a <= b && con_b == 2)) {
                res.push_back('a');
                --a;
                ++con_a;
                con_b = 0;
            } else {
                res.push_back('b');
                --b;
                ++con_b;
                con_a = 0;
            }
        }

        return res;
    }
};
````
