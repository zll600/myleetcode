# [680. Valid Palindrome II](https://leetcode-cn.com/problems/valid-palindrome-ii/)

## 题目

Given a string `s`, return `true` *if the* `s` *can be palindrome after deleting **at most one** character from it*.

 

**Example 1:**

```
Input: s = "aba"
Output: true
```

**Example 2:**

```
Input: s = "abca"
Output: true
Explanation: You could delete the character 'c'.
```

**Example 3:**

```
Input: s = "abc"
Output: false
```

 

**Constraints:**

- `1 <= s.length <= 105`
- `s` consists of lowercase English letters.

## 题目大意

给定一个字符串 `s`，如果 `s` 可以通过删除至多一个字符使其回文化，就返回 `true`，否则返回 `false`，


## 解题思路

### Solution 1: Two pointers

判断回文串最常用的方法就是双指针

这里在遇到第一组不相等的时候，就会分别判断，从左边删一个和从右边删一个，那个可能会成功


````c++
class Solution {
public:
    bool validPalindrome(string s) {
        const int len = s.size();
        int left = 0, right = s.size() - 1;
        
        // [left, right] 循环不变量
        while (left < right) {
            if (s[left] != s[right]) {
                // 删除一个
                return IsValid(s, left, right - 1) || IsValid(s, left + 1, right);
            }
            ++left;
            --right;
        }
        
        return true;
    }
    
  private:
    bool IsValid(const string& str, int left, int right) {
        while (left < right) {
            if (str[left] != str[right]) {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};
````

### Solution 2:



````c++
````
