# [1015. Smallest Integer Divisible by K](https://leetcode.cn/problems/smallest-integer-divisible-by-k/)

## 题目

Given a positive integer `k`, you need to find the **length** of the **smallest** positive integer `n` such that `n` is divisible by `k`, and `n` only contains the digit `1`.

Return *the **length** of* `n`. If there is no such `n`, return -1.

**Note:** `n` may not fit in a 64-bit signed integer.

 

**Example 1:**

```
Input: k = 1
Output: 1
Explanation: The smallest answer is n = 1, which has length 1.
```

**Example 2:**

```
Input: k = 2
Output: -1
Explanation: There is no such positive integer n divisible by 2.
```

**Example 3:**

```
Input: k = 3
Output: 3
Explanation: The smallest answer is n = 111, which has length 3.
```

 

**Constraints:**

- `1 <= k <= 105`

## 题目大意

给定正整数 `k` ，你需要找出可以被 `k` 整除的、仅包含数字 `1` 的最 小 正整数 `n` 的长度

返回 `n` 的长度。如果不存在这样的 `n` ，就返回 `-1`

注意： n 不符合 64 位带符号整数

## 解题思路 

### Solution 1: Math

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/smallest-integer-divisible-by-k/solution/javajie-fa-yi-ji-zheng-ming-de-si-lu-by-jiangzk/)

这里利用了取模的一些数学性质，不太好想

````c++
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) {
            return -1;
        }
        
        int num = 1;
        int len = 1;
        while (num % k != 0) {
            num %= k;
            num = num * 10 + 1;
            ++len;
        }
        return len;
    }
};
````
