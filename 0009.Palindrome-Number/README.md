# [9. Palindrome Number](https://leetcode.com/problems/palindrome-number/)

Given an integer `x`, return `true` if `x` is palindrome integer.

An integer is a **palindrome** when it reads the same backward as forward. For example, `121` is palindrome while `123` is not.

 

**Example 1:**

```
Input: x = 121
Output: true
```

**Example 2:**

```
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
```

**Example 3:**

```
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
```

**Example 4:**

```
Input: x = -101
Output: false
```

 

**Constraints:**

- `-231 <= x <= 231 - 1`

 

**Follow up:** Could you solve it without converting the integer to a string?

## 题目大意

给定一个则整数 x，如果 x是回文整数，返回 true

如果一个整数从前往后读，从后往前读是一样的，

## 解题思路

### 解法1（将数字转化为字符串）

先将数字转化为字符串，然后得到反转后的字符串，比较两者是否相等

`````c++
class Solution {
public:
    bool isPalindrome(int x) {
        string src = to_string(x);
        string tmp(src.rbegin(), src.rend());
        
        return src == tmp;
    }
};
`````

### 解法2（将数字的每一位逆序）

这种方法在逆序的时候需要考虑是否会发生溢出，

特殊情况，负数不可能是回文数 

`````c++
class Solution {
public:
    bool isPalindrome(int x) {
        if (x <  0) {  // 如果是负数则一定不满足要求
            return false;
        }
        
        int src = x;
        int num = 0;
        int cur = 0;
        
        while (x) {
            cur = x % 10;
            // 这里是为了避免溢出
            if (num > INT_MAX / 10 || (num == INT_MAX / 10 && cur > INT_MAX % 10)) {
                return false;
            }
            num = num * 10 + cur;
            x /= 10;
        }
        
        return num == src;
    }
};
`````

