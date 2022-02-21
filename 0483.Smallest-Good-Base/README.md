# [483. Smallest Good Base](https://leetcode.com/problems/smallest-good-base/)

## 题目

Given an integer `n` represented as a string, return *the smallest **good base** of* `n`.

We call `k >= 2` a **good base** of `n`, if all digits of `n` base `k` are `1`'s.

 

**Example 1:**

```
Input: n = "13"
Output: "3"
Explanation: 13 base 3 is 111.
```

**Example 2:**

```
Input: n = "4681"
Output: "8"
Explanation: 4681 base 8 is 11111.
```

**Example 3:**

```
Input: n = "1000000000000000000"
Output: "999999999999999999"
Explanation: 1000000000000000000 base 999999999999999999 is 11.
```

 

**Constraints:**

- `n` is an integer in the range `[3, 1018]`.
- `n` does not contain any leading zeros.

## 题目大意

以字符串的形式给出 `n`, 以字符串的形式返回 `n` 的 最小 **好进制** 

如果 `n` 的  `k(k>=2)` 进制数的所有数位全为1，则称 `k(k>=2)` 是 `n` 的一个 好进制

## 解题思路

这里要解决的问题有：
- 怎么求出 n 的好进制
- 怎么求出 n 的最小好进制


### Solution 1: Math

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/smallest-good-base/solution/shu-xue-fang-fa-fen-xi-dai-ma-by-zerotrac/)

````c++
class Solution {
public:
    string smallestGoodBase(string n) {
        long long num = stoll(n);
        long long ans = num - 1;

        for (int i = 59; i >= 2; --i) {
            int k = pow(num, 1.0 / i);

            if (k > 1) {
                long long sum = 1, mul = 1;
                for (int j = 1; j <= i; ++j) {
                    mul *= k;
                    sum += mul;
                }

                if (num == sum) {
                    ans = k;
                    break;
                }
            }
        }
        return to_string(ans);
    }
};
````
