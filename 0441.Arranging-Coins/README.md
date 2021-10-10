# [441. Arranging Coins](https://leetcode.com/problems/arranging-coins/)

## 题目

You have `n` coins and you want to build a staircase with these coins. The staircase consists of `k` rows where the `ith` row has exactly `i` coins. The last row of the staircase **may be** incomplete.

Given the integer `n`, return *the number of **complete rows** of the staircase you will build*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/09/arrangecoins1-grid.jpg)

```
Input: n = 5
Output: 2
Explanation: Because the 3rd row is incomplete, we return 2.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/04/09/arrangecoins2-grid.jpg)

```
Input: n = 8
Output: 3
Explanation: Because the 4th row is incomplete, we return 3.
```

 

**Constraints:**

- `1 <= n <= 231 - 1`



## 题目大意

你有 n 枚硬币，你想要将他们摆放为阶梯状，第 k 行需要恰好有 k 个硬币，最后一行可能是不完整的，

给定一个整数 n ，返回你可以得到的完整的行数

## 解体思路

这道题目并不难，但是想要做好，还是要用一些技巧

### 解法1

暴力解法，遍历每一个可能的答案，效率并不高

```c++
class Solution {
public:
    int arrangeCoins(int n) {
        int rows = 1;
        while (n >= rows) {
            n -= rows;
            ++rows;
        }
        return rows - 1;
    }
};
```

## 解法2（二分）

从题目中可以得到 rows 的取值范围一定在 [1, n] 之间，所以可以利用二分查找来加速这个过程

这里也用到了一些数学技巧，这道题目中有一处必须要用到 long，否则无法通过

```c++
class Solution {
public:
    int arrangeCoins(int n) {
        int left = 1;
        int right = n;
        
        while (left < right) {
            int mid = left + (right - left + 1) / 2;  // 这种写法可以避免溢出
            long  need = 1L * (mid + 1) * mid / 2;  // 这里必须用 long ，否则会发生溢出 
            
            if (n >= need) {  // 找到满足条件的最后一个
                left = mid;
            } else {
                right = mid - 1;
            }
            
        }
        
        return right;
    }
};
```

