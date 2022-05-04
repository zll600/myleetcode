# [1017. Convert to Base -2](https://leetcode.com/problems/convert-to-base-2/)

## 题目

Given an integer `n`, return *a binary string representing its representation in base* `-2`.

**Note** that the returned string should not have leading zeros unless the string is `"0"`.

 

**Example 1:**

```
Input: n = 2
Output: "110"
Explantion: (-2)2 + (-2)1 = 2
```

**Example 2:**

```
Input: n = 3
Output: "111"
Explantion: (-2)2 + (-2)1 + (-2)0 = 3
```

**Example 3:**

```
Input: n = 4
Output: "100"
Explantion: (-2)2 = 4
```

 

**Constraints:**

- `0 <= n <= 109`

## 题目大意

给出数字 N，返回由若干 “0” 和 “1"组成的字符串，该字符串为 N 的负二进制（base -2）表示。除非字符串就是 “0”，否则返回的字符串中不能含有前导零。

## 解题思路

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1000~1099/1017.Convert-to-Base-2/)

参考十进制转化为 二进制，使用短除法，如果余数出现负数，转化为正数，并且修改 n 即可

````c++
class Solution {
public:
    string baseNeg2(int n) {
        if (n == 0) {
            return "0";
        }
        
        string res = "";
        
        while (n != 0) {
            int remainder = n % (-2);
            n /= (-2);
            // 如果余数为负
            if (remainder < 0) {
                remainder += 2;
                ++n;
            }
            res = to_string(remainder) + res;
        }
        return res;
    }
};
````
