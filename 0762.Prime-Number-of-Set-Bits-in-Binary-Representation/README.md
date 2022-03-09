# [762. Prime Number of Set Bits in Binary Representation](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/)

## 题目

Given two integers `left` and `right`, return *the **count** of numbers in the **inclusive** range* `[left, right]` *having a **prime number of set bits** in their binary representation*.

Recall that the **number of set bits** an integer has is the number of `1`'s present when written in binary.

- For example, `21` written in binary is `10101`, which has `3` set bits.

 

**Example 1:**

```
Input: left = 6, right = 10
Output: 4
Explanation:
6  -> 110 (2 set bits, 2 is prime)
7  -> 111 (3 set bits, 3 is prime)
8  -> 1000 (1 set bit, 1 is not prime)
9  -> 1001 (2 set bits, 2 is prime)
10 -> 1010 (2 set bits, 2 is prime)
4 numbers have a prime number of set bits.
```

**Example 2:**

```
Input: left = 10, right = 15
Output: 5
Explanation:
10 -> 1010 (2 set bits, 2 is prime)
11 -> 1011 (3 set bits, 3 is prime)
12 -> 1100 (2 set bits, 2 is prime)
13 -> 1101 (3 set bits, 3 is prime)
14 -> 1110 (3 set bits, 3 is prime)
15 -> 1111 (4 set bits, 4 is not prime)
5 numbers have a prime number of set bits.
```

 

**Constraints:**

- `1 <= left <= right <= 106`
- `0 <= right - left <= 104`

## 题目大意

给定两个整数 `left` 和 `right`，返回在闭区间 `[left, right]` 中二进制表示方法中有多少个数字含有素数个 1，

## 解题思路

需要解决的问题有：

- 找到这个数的二进制表达式中有多少个 1
- 判断 1 出现的次数是否为 素数个

### Solution 1:

这种解法会超时，但我觉得已经没有可以优化的地方了

````c++
class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        int res = 0;
        for (int i = left; i <= right; ++i) {
            if (IsPrime(GetOnes(i))) {
                ++res;
            }
        }
        return res;
    }
    
 private:
    // 判断是否为 素数
    bool IsPrime(int cnt) {
        return cnt == 2
            || cnt ==3
            || cnt == 5
            || cnt == 7
            || cnt == 11
            || cnt == 13
            || cnt == 17
            || cnt == 19;
    }
    
    // 得到 1 的数目
    int GetOnes(int num) {
        int cnt = 0;
        while (num) {
            cnt += num & 1;
            num >> 1;
        }
        return cnt;
    }
};
````

### Solution 2:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/prime-number-of-set-bits-in-binary-representation/solution/cchao-100de-jian-dan-jie-fa-by-ffreturn-pj11/)

这里使用了一个内置函数来计算 1 的数目

````c++
class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        int res = 0;
        for (int i = left; i <= right; ++i) {
            res += primes[__builtin_popcount(i)];
        }

        return res;
    }

 private:
    const vector<int> primes = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1};

};
````
