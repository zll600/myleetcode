# [344. Reverse String](https://leetcode.com/problems/reverse-string/)

## 题目

Write a function that reverses a string. The input string is given as an array of characters `s`.

 

**Example 1:**

```
Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
```

**Example 2:**

```
Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s[i]` is a [printable ascii character](https://en.wikipedia.org/wiki/ASCII#Printable_characters).

 

**Follow up:** Do not allocate extra space for another array. You must do this by modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm) with `O(1)` extra memory.

## 题目大意

编写一个函数反转一个字符串，

进阶要求：原地反转

## 解题思路

这道题比较简单，即使其进阶问题也是

### 解法1

双指针一遍搞定

````c++
class Solution {
public:    
    void reverseString(vector<char>& s) {
        // 双指针对碰
        for (int i = s.size() - 1, j = 0; j < i; j++, i--) {
            swap(s[i], s[j]);
        }
    }
};
````

