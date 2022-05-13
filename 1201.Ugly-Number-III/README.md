# [1201. Ugly Number III](https://leetcode.com/problems/ugly-number-iii/)

## 题目

An **ugly number** is a positive integer that is divisible by `a`, `b`, or `c`.

Given four integers `n`, `a`, `b`, and `c`, return the `nth` **ugly number**.

 

**Example 1:**

```
Input: n = 3, a = 2, b = 3, c = 5
Output: 4
Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
```

**Example 2:**

```
Input: n = 4, a = 2, b = 3, c = 4
Output: 6
Explanation: The ugly numbers are 2, 3, 4, 6, 8, 9, 10, 12... The 4th is 6.
```

**Example 3:**

```
Input: n = 5, a = 2, b = 11, c = 13
Output: 10
Explanation: The ugly numbers are 2, 4, 6, 8, 10, 11, 12, 13... The 5th is 10.
```

 

**Constraints:**

- `1 <= n, a, b, c <= 109`
- `1 <= a * b * c <= 1018`
- It is guaranteed that the result will be in range `[1, 2 * 109]`.

## 题目大意

请你帮忙设计一个程序，用来找出第 `n` 个丑数。丑数是可以被 `a` 或 `b` 或 `c` 整除的 正整数

## 解题思路

在一个有序的区间中，查找某个给定的值，可以使用二分查找来降低时间复杂度，这里二分查找的是 [1, 2 * 1e9]

所以这道题目的难点在于 check 喊出的编码，如何快速确定某个区间中有多少个丑数

n / a 有多少个 a 的倍数
n / b 有多少个 b 的倍数
n / c 有多少个 c 的倍数

如果仅仅这样计数会造成重复，这里可以利用 维恩图 来画出这三个集合的关系,最后求出没有重复的数的个数
n / (ab / gcd(a, b)) 既可以被 a 整除的数，也可以被 b 整除的数
n / (bc / gcd(b, c)) 既可以被 b 整除的数，也可以被 c 整除的数
n / (ac / gcd(a, c)) 既可以被 a 整除的数，也可以被 c 整除的数
n / (abc / gcd(ab, c)) 既可以被 ab 整除的数，也可以被 c 整除的数

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1200~1299/1201.Ugly-Number-III/)

````Go
func nthUglyNumber(n int, a int, b int, c int) int {
    low, high := int64(0), int64(2*1e9)
    for low < high {
        mid := low + (high - low) >> 1
        if calcNth(mid, int64(a), int64(b), int64(c)) < int64(n) {
            low = mid + 1
        } else {
            high = mid
        }
    }
    return int(low)
}

func calcNth(num, a, b, c  int64) int64 {
    ab, bc, ac := a * b / gcd(a, b), b * c / gcd(b, c), a * c / gcd(a, c)
    abc := ab * c / gcd(ab, c)
    return num / a + num / b + num / c - num / ab - num / bc - num / ac + num / abc
}

func gcd(a, b int64) int64 {
    for b != 0 {
        a, b = b, a % b
    }
    return a
}
````



````Go
````
