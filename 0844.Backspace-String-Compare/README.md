# [844. Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/)

## 题目

Given two strings `s` and `t`, return `true` *if they are equal when both are typed into empty text editors*. `'#'` means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

 

**Example 1:**

```
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".
```

**Example 2:**

```
Input: s = "ab##", t = "c#d#"
Output: true
Explanation: Both s and t become "".
```

**Example 3:**

```
Input: s = "a#c", t = "b"
Output: false
Explanation: s becomes "c" while t becomes "b".
```

 

**Constraints:**

- `1 <= s.length, t.length <= 200`
- `s` and `t` only contain lowercase letters and `'#'` characters.

 

**Follow up:** Can you solve it in `O(n)` time and `O(1)` space?

## 题目大意

给定两个字符串`s` 和 `t`，`'#'`表示回退一个字符，如果两个字符串最终相等，返回 `true`

注意，如果对空文本输入退隔字符，依旧是空文本

## 解题思路

这道题可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0844.Backspace-String-Compare/

### Solution 1: 利用栈来模拟

这种解法就是利用栈来模拟，如果遇到 '#'，就回退一个字符，这里注意如果有多余的 '#'，是不加入

但是这种解法占用的内存不满足题意

```c++
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        vector<char> str1;
        for (char c : s) {
            if (c == '#') {
                // 如果是'#'，‘#’不计入结果字符中
                if (!str1.empty()) {
                    // 如果有字符可以回退
                    str1.pop_back();
                }
            } else {
                str1.push_back(c);
            }
        }
        
        vector<char> str2;
        for (char c : t) {
            if (c == '#') {
                if (!str2.empty()) {
                    str2.pop_back();
                }
            } else {
                str2.push_back(c);
            }
        }
        
        return string(str1.begin(), str1.end()) == string(str2.begin(), str2.end());
    }
};
```

### Solution 2: Two pointers

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/backspace-string-compare/solution/shuang-zhi-zhen-bi-jiao-han-tui-ge-de-zi-8fn8/

这种解法利用双指针来分别遍历两个数组，因为 '#' 只会回退左边的字符，所以右边的字符不受影响，这里采用倒序遍历，遍历过程中统计出现的 '#'，会影响后续遍历到的字符



````c++
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        const int len1 = s.size();
        const int len2 = t.size();
        
        int skip1 = 0, skip2 = 0;
        int idx1 = len1 - 1, idx2 = len2 - 1;
        while (idx1 >= 0 || idx2 >= 0) {
            // 处理字符串 s
            while (idx1 >= 0) {
                if (s[idx1] == '#') {
                    // 统计后面遍历时可以跳过多少字符
                    --idx1;
                    ++skip1;
                } else if (s[idx1] != '#' && skip1 > 0) {
                    // 如果可以回退择直接回退
                    --skip1;
                    --idx1;
                } else {
                    break;
                }
            }
            
            // 处理字符串 t
            while (idx2 >= 0) {
                if (t[idx2] == '#') {
                    --idx2;
                    ++skip2;
                } else if (t[idx2] != '#' && skip2 > 0) {
                    --skip2;
                    --idx2;
                } else {
                    break;
                }
            }
            
            if (idx1 >= 0 && idx2 >= 0) {
                // 如果还有字符串，需要对相应位置的字符进行比较
                if (s[idx1] != t[idx2]) {
                    return false;
                }
            } else {
                if (idx1 >= 0 || idx2 >= 0) {
                    // 如果长度不行等等原因
                    return false;
                }
            }
            --idx1;
            --idx2;
        }
        return true;
    }
};
````



