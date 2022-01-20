# [796. Rotate String](https://leetcode-cn.com/problems/rotate-string/)

## 题目

Given two strings `s` and `goal`, return `true` *if and only if* `s` *can become* `goal` *after some number of **shifts** on* `s`.

A **shift** on `s` consists of moving the leftmost character of `s` to the rightmost position.

- For example, if `s = "abcde"`, then it will be `"bcdea"` after one shift.

 

**Example 1:**

```
Input: s = "abcde", goal = "cdeab"
Output: true
```

**Example 2:**

```
Input: s = "abcde", goal = "abced"
Output: false
```

 

**Constraints:**

- `1 <= s.length, goal.length <= 100`
- `s` and `goal` consist of lowercase English letters.

## 题目大意

给定两个字符串, `A` 和 `B`

`A` 的旋转操作就是将 `A` 最左边的字符移动到最右边。 例如, 若 `A` = `'abcde'`，在移动一次之后结果就是`'bcdea'` 。如果在若干次旋转操作之后，`A` 能变成`B`，那么返回True。



## 解题思路

* 这道题目的一个难点在于这些字母时要满足一定的顺序性，

### Solution 1: 

这种解法，找到 s 中从某一位置到结尾，是否和goal 从开始位置相同的子字符串是否相等来做，

```c++
class Solution {
public:
    bool rotateString(string s, string goal) {
        const int len = s.size();
        int idx = 0;
        while (idx < len) {
            // 找到 s 的前半段和 goal 的后半段相同的位置
            if (s.substr(idx) == goal.substr(0, len - idx)) {
                // s[idx, len - 1] == goal[0, len - idx]
                break;
            }
            ++idx;
        }
        if (idx == len) {
            // 如果没有相同的，就直接返回 false 即可
            return false;
        }
        
        string tmp = s.substr(idx);
        // cout << tmp << "---";
        tmp += s.substr(0, idx);
        // cout << tmp << endl;
        
        return tmp == goal;
    }
};
```

### Solution 2:

将两字符串相加，判断其中是否包含 goal

```c++
class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) {
            // 如果长度都不相等，直接返回
            return false;
        }
        const int len = s.size();
        string tmp = s + s; // 拼接字符串
        int pos = tmp.find(goal);
        return pos != string::npos;
    }
};
```

