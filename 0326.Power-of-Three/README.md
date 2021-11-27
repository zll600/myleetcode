# [326. Power of Three](https://leetcode.com/problems/power-of-three/)

## 题目

Given an integer `n`, return *`true` if it is a power of three. Otherwise, return `false`*.

An integer `n` is a power of three, if there exists an integer `x` such that `n == 3x`.

 

**Example 1:**

```
Input: n = 27
Output: true
```

**Example 2:**

```
Input: n = 0
Output: false
```

**Example 3:**

```
Input: n = 9
Output: true
```

**Example 4:**

```
Input: n = 45
Output: false
```

 

**Constraints:**

- `-231 <= n <= 231 - 1`

 

**Follow up:** Could you solve it without loops/recursion?

## 题目大意

判断一个数是否是 3 的幂

## 解题思路

这道题目用循环肯定是可以解决的，但是题目要求不使用循环

与此类似还有第 231 题2 的幂，342、4 的幂

### Solution 1: Loop

````c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        while (n >= 3) {
            if (n % 3 == 0) {
                // 如果能被 3 整除
                n /= 3;
            } else {
                // 如果不能被 3 整除
                return false;
            }
        }
        // 整除到最后一定等于 1
        return n == 1;
    }
};
````

### Solution 2:

使用缓存，也称“打表法”

````c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        unordered_set<int> cache;

        int num = 1;
        cache.insert(num);
        while (num <= INT_MAX / 3) {
            // 这种写法可以保证不会发生越界
            num *= 3;
            cache.insert(num);
        }
        
        if (cache.find(n) == cache.end()) {
            return false;
        }
        return true;
    }
};
````

### Solution 3:

这种方法可以参考这篇题解：https://leetcode-cn.com/problems/power-of-three/solution/gong-shui-san-xie-yi-ti-san-jie-shu-xue-8oiip/

需要一些数论的知识，这个暂时不太会

```c++
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};
```

