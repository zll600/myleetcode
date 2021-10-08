# [434. Number of Segments in a String](https://leetcode.com/problems/number-of-segments-in-a-string/)

## 题目

You are given a string `s`, return *the number of segments in the string*. 

A **segment** is defined to be a contiguous sequence of **non-space characters**.

 

**Example 1:**

```
Input: s = "Hello, my name is John"
Output: 5
Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
```

**Example 2:**

```
Input: s = "Hello"
Output: 1
```

**Example 3:**

```
Input: s = "love live! mu'sic forever"
Output: 4
```

**Example 4:**

```
Input: s = ""
Output: 0
```

 

**Constraints:**

- `0 <= s.length <= 300`
- `s` consists of lower-case and upper-case English letters, digits or one of the following characters `"!@#$%^&*()_+-=',.:"`.
- The only space character in `s` is `' '`.

## 题目大意

给定一个字符串 s，返回字符串中多有分段的数目，

一个分段被定义为一个串连续的没有空格的字符序列

## 解题思路

这道题的思路不难，但是细节还是挺重要的，

这里提前说明，不能一 `' '`为分隔符来计算有多少段，如果整个字符串全部为空白，这种做法得出来的分段不是 0，而是有多少个空白

### 解法1

我真里用了一个标记，保证是一个合理的分段开头，知道遇到一个空白，才累加结果，并恢复标志，注意对最后一个的的判断

`````c++
class Solution {
public:
    int countSegments(string s) {
        if (s.empty()) {
            return 0;
        }
        
        int res = 0;
        bool flag = false;
        for (char c : s) {
            if (c == ' ' && flag) {  // 遇到一个空白，且已经开始了一个段，说明到了段的末尾
                res++;
                flag = false;  // 恢复
            } else if (c != ' ') {  // 如果不是空白，说明开始了一个新的段
                flag = true;
            }
        }
        
        // 这里是为了不漏掉最后个不是空白的分段
        if (*s.crbegin() != ' ' && flag) {
            res++;
        }
        
        return res;
    }
};
`````

## 解法2

再遍历的过程中统计单词，这里注意下标的问题，因为 for 循环中有一次 i++，需要判断这次操作会不会影响程序最后的结果

````c++
class Solution {
public:
    int countSegments(string s) {
        if (s.empty()) {
            return 0;
        }
        
        int res = 0;
        int size = s.size();
        for (int i = 0; i < size; i++) {
            if (s[i] == ' ') {
                continue;
            }
            
            while (i < size && s[i] != ' ') {
                i++;
            }
            // 注意此时的 i 位置是一个空白，for 循环中会再次递增一次 i，
            // 但是也就只是跳过了这个空白，对最终的结果没有影响，
            // 这里也可以删掉for 循环中的 i++
            
            res++;
        }
        return res;
    }
};
````

