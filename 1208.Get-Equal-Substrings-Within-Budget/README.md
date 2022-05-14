# [1208. Get Equal Substrings Within Budget](https://leetcode.com/problems/get-equal-substrings-within-budget/)

## 题目

You are given two strings `s` and `t` of the same length. You want to change `s` to `t`. Changing the `i`-th character of `s` to `i`-th character of `t` costs `|s[i] - t[i]|` that is, the absolute difference between the ASCII values of the characters.

You are also given an integer `maxCost`.

Return the maximum length of a substring of `s` that can be changed to be the same as the corresponding substring of `t`with a cost less than or equal to `maxCost`.

If there is no substring from `s` that can be changed to its corresponding substring from `t`, return `0`.

 

**Example 1:**

```
Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3
Explanation: "abc" of s can change to "bcd". That costs 3, so the maximum length is 3.
```

**Example 2:**

```
Input: s = "abcd", t = "cdef", maxCost = 3
Output: 1
Explanation: Each character in s costs 2 to change to charactor in t, so the maximum length is 1.
```

**Example 3:**

```
Input: s = "abcd", t = "acde", maxCost = 0
Output: 1
Explanation: You can't make any change, so the maximum length is 1.
```

 

**Constraints:**

- `1 <= s.length, t.length <= 10^5`
- `0 <= maxCost <= 10^6`
- `s` and `t` only contain lower case English letters.

## 题目大意

给你两个长度相同的字符串，`s` 和 `t`。将 `s` 中的第 `i` 个字符变到 `t` 中的第 `i` 个字符需要 `|s[i] - t[i]|` 的开销（开销可能为 `0`），也就是两个字符的 `ASCII` 码值的差的绝对值

用于变更字符串的最大预算是 `maxCost`。在转化字符串时，总开销应当小于等于该预算，这也意味着字符串的转化可能是不完全的。

如果你可以将 `s` 的子字符串转化为它在 `t` 中对应的子字符串，则返回可以转化的最大长度。如果 s 中没有子字符串可以转化成 `t` 中对应的子字符串，则返回 `0`

## 解题思路

这类求连续子数组的最大长度的问题可以想到使用滑动窗口来做，

- 窗口扩大的条件就是 剩余的开销依旧可以满足字符转化的需要
- 窗口缩小的条件就是剩余的开销无法满足字符转化的需要

所以这里的难点在于如果实现这个滑动窗口，这里还必须考虑 k = 0 等特殊情况，所以还是有难度在 解法2 中找到了一个模板，这个模板是可以实现这个功能的

### Solution 1: Sliding windown

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1200~1299/1208.Get-Equal-Substrings-Within-Budget/)

````
func equalSubstring(s string, t string, maxCost int) int {
    left, right, res := 0, 0, 0
    for left < len(s) {
        if right < len(s) && maxCost >= abs(int(s[right]) - int(t[right])) {
            maxCost -= abs(int(s[right] - 'a') - int(t[right] - 'a'))
            right++
            res = max(res, right - left)
        } else {
            maxCost += abs(int(s[left] - 'a') - int(t[left] - 'a'))
            left++
        }
        // fmt.Println(left, " --- ", right)
    }
    return res
}

func abs(num int) int {
    if num < 0 {
        return -1 * num
    }
    return num
}

func max(a, b int) int {
    if b > a {
        return b
    }
    return a
}
````

### Solution 2: Sliding window

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/get-equal-substrings-within-budget/solution/fen-xiang-zhen-cang-de-hua-dong-chuang-k-e3rd/)

````python3
class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        n = len(s)
        costs = [0] * n
        for i in range(n):
            costs[i] = abs(ord(s[i]) - ord(t[i]))

        left, right = 0, 0
        res = 0
        sums = 0
        while right < n:
            sums += costs[right]
            while sums > maxCost:
                sums -= costs[left]
                left += 1
            res = max(res, right - left + 1)
            right += 1

        return res
````
