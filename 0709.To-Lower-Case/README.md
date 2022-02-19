# [709. To Lower Case](https://leetcode.com/problems/to-lower-case/)

## 题目



Given a string `s`, return *the string after replacing every uppercase letter with the same lowercase letter*.

 

**Example 1:**

```
Input: s = "Hello"
Output: "hello"
```

**Example 2:**

```
Input: s = "here"
Output: "here"
```

**Example 3:**

```
Input: s = "LOVELY"
Output: "lovely"
```

 

**Constraints:**

- `1 <= s.length <= 100`
- `s` consists of printable ASCII characters.

## 题目大意

给定一个字符串 `s`,返回 *替换每个大写字母为同样的小写字母之后的字符串*

## 解题思路

根据题目要求,将大写字母转化为小写字母,

### Solution 1:

````c++
class Solution {
public:
    string toLowerCase(string s) {
        for (char& c : s) {
            if (::isupper(c)) {
                c = ::tolower(c);
            }
        }

        return s;
    }
};
````
