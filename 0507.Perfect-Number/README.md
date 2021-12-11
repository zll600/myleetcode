# [507. Perfect Number](https://leetcode-cn.com/problems/perfect-number/)

A [**perfect number**](https://en.wikipedia.org/wiki/Perfect_number) is a **positive integer** that is equal to the sum of its **positive divisors**, excluding the number itself. A **divisor** of an integer `x` is an integer that can divide `x` evenly.

Given an integer `n`, return `true` *if* `n` *is a perfect number, otherwise return* `false`.

 

**Example 1:**

```
Input: num = 28
Output: true
Explanation: 28 = 1 + 2 + 4 + 7 + 14
1, 2, 4, 7, and 14 are all divisors of 28.
```

**Example 2:**

```
Input: num = 6
Output: true
```

**Example 3:**

```
Input: num = 496
Output: true
```

**Example 4:**

```
Input: num = 8128
Output: true
```

**Example 5:**

```
Input: num = 2
Output: false
```

 

**Constraints:**

- `1 <= num <= 108`

## 题目大意

对于一个 **正整数**，如果它和除了它自身以外的所有 **正因子** 之和相等，我们称它为 「完美数」。

给定一个数，判断它是否是完美数，

## 解题思路

### Solution 1: 打表

求完美数，根据题目给定的范围，这里可以确定 1e8 内的完美数，不过，采用打表法即可

```c++
class Solution {
public:
    bool checkPerfectNumber(int num) {
        return num == 6 || num == 28 || num == 496 || num == 8128 || num == 33550336;
    }
};
```

### Solution 2:

````c++
class Solution {
public:
    bool checkPerfectNumber(int num) {
        if (num <= 1) {
            // 1 必定不满足条件
            return false;
        }
        
        int sum = 1;
        int bound = static_cast<int>(sqrt(num)) + 1; // 这里只需要查询到平方根的位置
        for (int i = 2; i < bound; ++i) {
            if (num % i != 0) { // 如果不能整除，则直接跳过
                continue;
            }
            
            int corr_div = num / i; // 得到另一个因数
            sum += corr_div + i;
        }
        
        return sum == num;
    }
};
````

