# [204. Count Primes](https://leetcode.com/problems/count-primes/) 

## 题目

Given an integer `n`, return *the number of prime numbers that are strictly less than* `n`.

 

**Example 1:**

```
Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
```

**Example 2:**

```
Input: n = 0
Output: 0
```

**Example 3:**

```
Input: n = 1
Output: 0
```

 

**Constraints:**

- `0 <= n <= 5 * 106`

## 题目大意

给定一个整数 n，返回严格小于整数 n 的质数的数目

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/count-primes/solution/ji-shu-zhi-shu-bao-li-fa-ji-you-hua-shai-fa-ji-you/

## 解题思路

### 解法1（暴力枚举（TLE））

这种解法，就是对每一个小于 n 的数进行判断，判断其是否为 质数，

```c++
class Solution {
public:
    int countPrimes(int n) {
        int res = 0;
        for (int i = 2; i < n; i++) {   // 判断每一个小于 n 的数，
            if (IsPrime(i)) {
                res++;
            }
        }
        return res;
    }

 private:
    bool IsPrime(int n) {
        for (int i = 2; i * i <= n; i++) {  // 这里有一个优化，不用判断所有，只要判断 i * i <= n
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }
};

```

### 优化

这个方法优化的地方在于不用判断所有偶数（除2 之外），

`````c++
class Solution {
public:
    int countPrimes(int n) {
        if (n < 3) {  // 处理边界情况
            return 0;
        }
        
        int res = 1;
        // 从 3 开始，所以初始值为 1 ，互为质数
        for (int i = 3; i < n; i++) {
            if ((i & 1) == 0) {  // 偶数一定不是质数，这里注意位运算的优先级
                continue;
            }
            
            if (IsPrime(i)) {  // 如果这个奇数是质数
                res++;
            }
        }
        
        return res;
    }

 private:
    bool IsPrime(int n) {
        // 主函数保证，传进来的都是奇数，所以直接从 3 开始，每次递增 2
        for (int i = 3; i * i <= n; i += 2) {  // 这里有一个优化，不用判断所有，只要判断 i * i <= n
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }
};

`````

### 解法3（埃式筛选）

这种做法在一次循环中，将所有质数的倍数标记为质数，然后在遍历一次统计结果

`````c++
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> is_not_prime(n);
        
        for (int i = 2; i < n; i++) {
            if (is_not_prime[i]) {
                continue;
            }
            
            // 将 i 的整数倍进行做标记，肯定不是质数了
            for (int j = i + i; j < n; j += i) {
                is_not_prime[j] = true;
            }
        }
        
        int res = 0;
        for (int i = 2; i < n; i++) {
            if (!is_not_prime[i]) {
                res++;
            }
        }
        
        return res;
    }
};

`````



