# [214. Shortest Palindrome](https://leetcode-cn.com/problems/shortest-palindrome/)

## 题目

You are given a string `s`. You can convert `s` to a palindrome by adding characters in front of it.

Return *the shortest palindrome you can find by performing this transformation*.

 

**Example 1:**

```
Input: s = "aacecaaa"
Output: "aaacecaaa"
```

**Example 2:**

```
Input: s = "abcd"
Output: "dcbabcd"
```

 

**Constraints:**

- `0 <= s.length <= 5 * 104`
- `s` consists of lowercase English letters only.

## 题目大意

给定一个字符串s，你可以在 s 的前面加入字符，使得 s 成为一个回文串，返回你可以得到的最短的字符串通过这个转化，

## 解题思路

这道题目转化一下，可以认为就是就反转的字符串和字符串本身的最长公共子串

### Solution 1: TLE

先反转整个字符串，反转之后，与原字符串进行匹配，得到结果，因为这种解法需要尝试每一种长度，所以最终回超时

````c++
class Solution {
public:
    string shortestPalindrome(string s) {
        if (s.empty()) {
            return s;
        }
        const int len = s.size();
        string rever = s;
        reverse(rever.begin(), rever.end()); // 反转字符串
        
        for (int i = len; i >= 0; --i) {
            // 找到最长的匹配的部分
            string str1 = s.substr(0, i);
            string str2 = rever.substr(len - i, i);
            if (str1 == str2) {
                // 将不匹配的部分，与原字符串拼接，
                return rever.substr(0, len - i) + s;
            }
        }
        return s + rever;
    }
};
````

### Solution 2:

这种解法，先判断出最长的回文子串，然后将不是回文的尾部部分，插入到字符串开头处

````c++
class Solution {
public:
    string shortestPalindrome(string s) {
        const int len = s.size(); // 长度
        
        // 找吹最长的回文子串
        // 反转不回文的部分，插入到字符串首部
        for (int i = len; i > 0; --i) {
            if (IsPalindrome(s.substr(0, i))) {
                string add = s.substr(i);
                reverse(add.begin(), add.end());
                return add + s;
            }
        }
        
        return ""; // 应该不会执行到这里，所以返回值影响不大
    }

 private:
    // 判断是否是回文子串
    bool IsPalindrome(const string& str) {
        const int len = str.size();
        int i = 0; 
        int j = len - 1;
        
        while (i < j) {
            if (str[i] != str[j]) {
                return false;
            }
            ++i;
            --j;
        }
        
        return true;
    }
};
````

