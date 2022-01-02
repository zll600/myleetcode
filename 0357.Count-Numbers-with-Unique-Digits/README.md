# [357. Count Numbers with Unique Digits](https://leetcode.com/problems/count-numbers-with-unique-digits/)

## 题目

Given an integer `n`, return the count of all numbers with unique digits, `x`, where `0 <= x < 10n`. 

**Example 1:**

```
Input: n = 2
Output: 91
Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, excluding 11,22,33,44,55,66,77,88,99
```

**Example 2:**

```
Input: n = 0
Output: 1
```

 

**Constraints:**

- `0 <= n <= 8`

## 题目大意

给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10^n 。

## 解题思路

这里需要注意，这里题目中求的是，对于各位数字都不相同，

这道题目可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0357.Count-Numbers-with-Unique-Digits/



这道题可以使用方法二先进行打表，然后再用方法一，效率会高一点，

### Solution 1: 打表

这里使用打表法，

````c++
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        const vector<int> res = {1, 10, 91, 739, 5275, 32491, 168571, 712891, 2345851, 5611771, 8877691};
        
        if (n >= 10) {
            return res[10];
        }
        
        return res[n];
    }
};
````

### Solution 2:

这里我们对每个区间的数计算所有的可能，这里使用的这种方法，可以减少一层循环，

当然这道题目也可以有别的解法，这里可以参考这篇题解：https://leetcode-cn.com/problems/count-numbers-with-unique-digits/solution/cchao-100de-dong-tai-gui-hua-by-ffreturn-hbzt/



````c++
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        }
        
        int res = 10; // 初始表示 0-9 这10个数
        int unique_num = 9; // 这里可以理解为 个位有 9 种可能
        int avail_num = 9; // 这里可以理解为 十位有 9 种可能
        while (n > 1 && avail_num > 0) {
            unique_num = unique_num * avail_num; // 这里用到了排列组合的知识
            res += unique_num; // 累加到结果中
            --avail_num; // 可以选择的数进行递减
            --n; // 减少
        }
        
        return res;
    }
};
````

