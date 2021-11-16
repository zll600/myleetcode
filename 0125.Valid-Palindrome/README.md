# [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/description/)

## 题目

A phrase is a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` *if it is a **palindrome**, or* `false` *otherwise*.

 

**Example 1:**

```
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
```

**Example 2:**

```
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
```

**Example 3:**

```
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
```

 

**Constraints:**

- `1 <= s.length <= 2 * 105`
- `s` consists only of printable ASCII characters.

## 题目大意

如果一个字符串在将所有的大些字母转化为小写字母，并且删除所有的非字母数字字符之后，是回文的，我们就说这个字符串是回文的，

## 解题思路

判断回文，我们一般需要使用两个位置，这道题目可以使用双指针

### Solution 1:

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0100~0199/0125.Valid-Palindrome/

````c++
class Solution {
public:
    bool isPalindrome(string s) {
        // 先将所有的大写字母转化为小写字母
        for (char& c : s) {
            c = tolower(c);
        }
        
        // 双指针，所有夹逼
        int left = 0, right = s.size() - 1;
        while (left < right) {
            // 跳过非字母非数字的部分
            while (left < right && !isalnum(s[left])) {
                ++left;
            }
            while (left < right && !isalnum(s[right])) {
                --right;
            }
            
            // 如果不相同，直接返回 false
            if (s[left] != s[right]) {
                return false;
            }
            ++left;
            --right;
        }
        
        return true;
    }
};
````



