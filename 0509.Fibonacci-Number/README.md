# [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)

## 题目

The **Fibonacci numbers**, commonly denoted `F(n)` form a sequence, called the **Fibonacci sequence**, such that each number is the sum of the two preceding ones, starting from `0` and `1`. That is,

```
F(0) = 0, F(1) = 1
F(n) = F(n - 1) + F(n - 2), for n > 1.
```

Given `n`, calculate `F(n)`.

 

**Example 1:**

```
Input: n = 2
Output: 1
Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
```

**Example 2:**

```
Input: n = 3
Output: 2
Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
```

**Example 3:**

```
Input: n = 4
Output: 3
Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
```

 

**Constraints:**

- `0 <= n <= 30`

## 题目大意

斐波那契数，通常用 F(n) 表示，形成的序列称为斐波那契数列。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

```
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
```

给定 N，计算 F(N)。

## 解题思路

这道题题目建议看看霜神的题解，里面涉及了很多这类问题的常用方法：https://books.halfrost.com/leetcode/ChapterFour/0500~0599/0509.Fibonacci-Number/

### Solution 1: DFS

````c++
class Solution {
public:
    int fib(int n) {
        if (n <= 1) {
            return n;
        }
        
        return fib(n - 1) + fib(n - 2);
    }
};  
````

### Solution 2: 自底向上 + 记忆化搜索

`````c++
class Solution {
public:
    int fib(int n) {
        if (n <= 1) {
            return n;
        }
        
        // 这里使用 map 做缓存，采用自底向上的递推过程
        unordered_map<int, int> cache;
        cache.emplace(0, 0);
        cache.emplace(1, 1);
        
        for (int i = 2; i <= n; ++i) {
            cache[i] = cache[i - 1] + cache[i - 2];
        }
        
        return cache.at(n);
    }
};  
`````

### Solution 3: 自顶向下 + 记忆化搜索

````c++
class Solution {
public:
    int fib(int n) {
        if (n <= 1) {
            return n;
        }
        
        // 这里现将 0， 1 放入
        unordered_map<int, int> cache = {
            {0, 0},
            {1, 1}
        };
        
        return Memorize(n, cache);
    }
    
 private:
    int Memorize(int n, unordered_map<int, int>& cache) {
        // 如果已经缓存过了，则直接返回
        if (cache.find(n) != cache.end()) {
            return cache.at(n);
        }
        // 没有缓存则进行计算
        cache[n] = Memorize(n - 1, cache) + Memorize(n - 2, cache);
        return cache[n];
    }
};  
````

### Solution 4: 空间优化后的 DP

````c++
class Solution {
public:
    int fib(int n) {
        if (n <= 1) {
            return n;
        }
        
        int first = 0;
        int second = 1;
        
        for (int i = 2; i <= n; ++i) {
            int cur = first + second;
            first = second;
            second = cur;
        }
        
        return second;
    }      
};
````

