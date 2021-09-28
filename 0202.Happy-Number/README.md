# [202. Happy Number](https://leetcode.com/problems/happy-number/)

## 题目

Write an algorithm to determine if a number `n` is happy.

A **happy number** is a number defined by the following process:

- Starting with any positive integer, replace the number by the sum of the squares of its digits.
- Repeat the process until the number equals 1 (where it will stay), or it **loops endlessly in a cycle** which does not include 1.
- Those numbers for which this process **ends in 1** are happy.

Return `true` *if* `n` *is a happy number, and* `false` *if not*.

 

**Example 1:**

```
Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

**Example 2:**

```
Input: n = 2
Output: false
```

 

**Constraints:**

- `1 <= n <= 231 - 1`

## 题目大意

判断一个数是否是快乐数，

一个快乐数满足如下定义：

* 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
* 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
* 如果 可以变为  1，那么这个数就是快乐数。

如果 n 是一个快乐数，返回true，否则返回 false

## 解题思路

### 解法1（利用哈希）

这道题利用了如果陷入无限循环，则最终会成环，这里我们利用一个哈希来判断是否成环

这里可以参考这篇题解：https://leetcode-cn.com/problems/happy-number/solution/kuai-le-de-zhi-shi-dian-zeng-jia-liao-by-sweetiee/

`````c++
class Solution {
 public:
    bool isHappy(int n) {
        unordered_set<int> cache;
        int cur = Sum(n);

        while (cur != 1) {
            if (cache.find(cur) != cache.end()) {
                return false;
            }

            cache.insert(cur);
            cur = Sum(cur);
        }
        return true;
    }

 private:
    int Sum(int n) {
        int res = 0;
        while (n) {
            res += (n % 10) * (n % 10);
            n /= 10;
        }

        return res;
    }
};
`````

