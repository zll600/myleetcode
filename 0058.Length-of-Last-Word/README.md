# [58. Length of Last Word](https://leetcode.com/problems/length-of-last-word/)

## 题目

Given a string `s` consisting of some words separated by some number of spaces, return *the length of the **last** word in the string.*

A **word** is a maximal substring consisting of non-space characters only.

 

**Example 1:**

```
Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
```

**Example 2:**

```
Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.
```

**Example 3:**

```
Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.
```

 

**Constraints:**

- `1 <= s.length <= 104`
- `s` consists of only English letters and spaces `' '`.
- There will be at least one word in `s`.

## 题目大意

给定一个由空格分开的单词组成的字符串，返回最后一个单词的长度

单词是指不含空格的最长的子串

## 解题思路

### 解法1

这道题目比较简单，跳过空格后从后向前遍历

``````c++
class Solution {
public:
    int lengthOfLastWord(string str) {
        int last = str.size() - 1;
        // 找到最后一个不为空格的位置
        while (last >= 0 && str[last] == ' ') {
            last--;
        }
        
        if (last < 0) {
            return 0;
        }
        
        int first = last;
        // 找到第一个是空格的位置
        while (first >= 0 && str[first] != ' ') {
            first--;
        }
        
        return last - first; // 注意这里是一个左开右闭区间
    }
};
``````

