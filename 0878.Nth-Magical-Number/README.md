# [878. Nth Magical Number](https://leetcode.com/problems/nth-magical-number/)

## 题目

A positive integer is *magical* if it is divisible by either `a` or `b`.

Given the three integers `n`, `a`, and `b`, return the `nth` magical number. Since the answer may be very large, **return it modulo** `109 + 7`.

 

**Example 1:**

```
Input: n = 1, a = 2, b = 3
Output: 2
```

**Example 2:**

```
Input: n = 4, a = 2, b = 3
Output: 6
```

 

**Constraints:**

- `1 <= n <= 109`
- `2 <= a, b <= 4 * 104`

## 题目大意

如果正整数可以被 `a` 或 `b` 整除，那么它是神奇的

返回第 n 个神奇数字。由于答案可能非常大，返回它模 `10^9 + 7` 的结果

## 解题思路



### Solution 1: Brute force

使用暴力解法，枚举所有值，直到知道第 n 个符合条件的结果

````c++
func nthMagicalNumber(n int, a int, b int) int {
    idx, num := 0, 1
    
    for idx < n {
        if num % a == 0 || num % b == 0 {
            idx++
        }
        
        num++
    }
    
    return num - 1
}
````

### Solution 2: BinarySearch

对于前 N 个数来说，能被 a 整除的数有 N / a 个，能被 b 整数的数有 N / b 个，能被 a or b 整除的数有 N / a + N / b - N / lcm(a, b)，由此就决定了整个二分的而 check 函数

接下来就是确定左右边界了

这里假设  a 是较小的值，如果不是才开始处做交换

那么第 n 个满足要求的数应该是 n * a，这里我们就可以确定了二分的右边界

因为 n * b > n * a，所以对于左边界这里可以设置为 n * a / 2

````c++
func nthMagicalNumber(n int, a int, b int) int {
    // 保证 a 是较小的值
    if a > b {
        a, b = b, a
    }

    // 设定左右边界
    low, high := a * n / 2, a * n
    for low < high {
        mid := low + (high - low) / 2

        if calc(mid, a, b) >= n {
            high = mid
        } else {
            low = mid + 1
        }
    }

    return low % 1000000007
}

// 利用辗转相除法来得到最大公倍数
func gcd(a, b int) int {
    if b == 0 {
        return a
    }

    return gcd(b, a % b)
}

// 求最小公倍数
func lcm(a, b int) int {
    return a * b / gcd(a, b)
}

// 求小于 n 的数中符合条件的有多少数
func calc(n, a, b int) int {
    return n / a + n / b - n / lcm(a, b)
}
````
