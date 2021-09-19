# [397. Integer Replacement](https://leetcode.com/problems/integer-replacement/)

## 题目

Given a positive integer `n`, you can apply one of the following operations:

1. If `n` is even, replace `n` with `n / 2`.
2. If `n` is odd, replace `n` with either `n + 1` or `n - 1`.

Return *the minimum number of operations needed for `n` to become `1`*.

 

**Example 1:**

```
Input: n = 8
Output: 3
Explanation: 8 -> 4 -> 2 -> 1
```

**Example 2:**

```
Input: n = 7
Output: 4
Explanation: 7 -> 8 -> 4 -> 2 -> 1
or 7 -> 6 -> 3 -> 2 -> 1
```

**Example 3:**

```
Input: n = 4
Output: 2
```

 

**Constraints:**

- `1 <= n <= 231 - 1`

## 题目大意

给定一个正整数，你可以对其应用下列任意选项：

* 如果 n 是偶数，用 n / 2 替换 n
* 如果 n 是奇数，用 n + 1 或者 n - 1替换 n

返回从 n 变成 1 需要的最少操作数

## 解题思路

* 首先看这道题，是求最优解，而且给了状态转移方程，并且属于无后效性问题，那就可以考虑动态规划，当然也可以用 DFS 和 BFS（留待以后实现），
* 这道题可以利用位运算的思路来解决：https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0397.Integer-Replacement/
  * 大致思路就是：如果是偶数，直接左移1 位，如果是奇数，要考虑是 +1 还是 -1，可以发现，除了 7 和 3 之外，所以 +1 成为 4 的倍数的数都适合 +1，对于 7，+1 和 -1都可以，对于 3 ，+1 比 -1 多一步，因此 3 需要特殊处理，
  * 将这个思路放在位运算的角度来考虑，如果最后两位 是 11 且不是3，适合+1，
  * 另外要考虑 INT_MAX 的特殊情况。

## 代码

````c++
class Solution {
public:
    int integerReplacement(int n) {
        if (n == INT_MAX) { // 这里需要处理溢出情况
            return 32;
        }
        
        int res = 0;
        
        while (n != 1) {
            if ((n & 1) == 0) { // 偶数直接 左移1位，
                n >>= 1;
            } else if ((n + 1) % 4 == 0 && n != 3) {    // 如果后两位是 11 ，则 +1 之后必然是 4 的倍数，则 + 1变为偶数
                ++n;
            } else {    // 后两位是 01，则减 1变为偶数
                --n;
            }
            ++res;
        }
        
        return res;
    }
};
````

