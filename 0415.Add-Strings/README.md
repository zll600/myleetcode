# [415. Add Strings](https://leetcode-cn.com/problems/add-strings/)

## 题目

Given two non-negative integers, `num1` and `num2` represented as string, return *the sum of* `num1` *and* `num2` *as a string*.

You must solve the problem without using any built-in library for handling large integers (such as `BigInteger`). You must also not convert the inputs to integers directly.

 

**Example 1:**

```
Input: num1 = "11", num2 = "123"
Output: "134"
```

**Example 2:**

```
Input: num1 = "456", num2 = "77"
Output: "533"
```

**Example 3:**

```
Input: num1 = "0", num2 = "0"
Output: "0"
```

 

**Constraints:**

- `1 <= num1.length, num2.length <= 104`
- `num1` and `num2` consist of only digits.
- `num1` and `num2` don't have any leading zeros except for the zero itself.

## 题目大意

给定用字符串表示的两个非负整数，并按照字符串的格式，返回他们的和，

## 解题思路

这种题一般不能将字符串转化为数字之后再进行计算，因为又可能会发生溢出，所以这里采用的方法是逐位进行计算，并用字符串的形式来存储结果，

### Solution 1: Two pointers

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/add-strings/solution/add-strings-shuang-zhi-zhen-fa-by-jyd/

循环可以继续的条件是任意一个数字没有遍历完，或者存在进位值

````C++
class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int idx1 = num1.size() - 1;
        int idx2 = num2.size() - 1;
        
        int carry = 0;
        while (idx1 >= 0 || idx2 >= 0 || carry != 0) {
            int cur1 = idx1 >= 0 ? num1[idx1] - '0' : 0;
            --idx1;
            int cur2 = idx2 >= 0 ? num2[idx2] - '0' : 0;
            --idx2;
            
            int sum = cur1 + cur2 + carry;
            carry = sum / 10;
            sum %= 10;
            
            res += to_string(sum);
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
````

