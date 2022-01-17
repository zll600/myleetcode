# [400. Nth Digit](https://leetcode.com/problems/nth-digit/)

Given an integer `n`, return the `nth` digit of the infinite integer sequence `[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...]`.

 

**Example 1:**

```
Input: n = 3
Output: 3
```

**Example 2:**

```
Input: n = 11
Output: 0
Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
```

 

**Constraints:**

- `1 <= n <= 231 - 1`

## 题目大意

给定一个整数 n，返回在无限整数序列的第 n 位

## 解题思路

### Solution 1:

这种解法可以参考这两篇题解：https://leetcode-cn.com/problems/nth-digit/solution/wei-rao-li-lun-mo-ni-ti-xian-ji-suan-gai-egzo/



这里可以先解决这两个问题：

1. 确定是 n 所对应的数字有几位
2. 确定具体是哪个数字



````c++
class Solution {
public:
    int findNthDigit(int n) {
        int digits = 1; // 位数
        int border = 9; // digits 位的数可以产生多少数
        
        // 这个循环用于确定 目标数 有几位数
        while (n > border * digits) {
            n -= border * digits; // 
            ++digits;
            border *= 10;
        }
        
        // 确定是哪一个数
        int offset = (n - 1) / digits; // 第几个 digits 位的数
        int begin = 1;
        for (int i = 0; i < digits - 1; ++i) {
            begin *= 10;
        }
        int mod = (n - 1) % digits; // 该数的第几位
        // 下面将整数转化为字符串，方便索引
        string target = to_string(offset+begin);
        return target[mod] - '0';
    }
};
````



