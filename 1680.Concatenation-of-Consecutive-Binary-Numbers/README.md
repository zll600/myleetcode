# [1680. Concatenation of Consecutive Binary Numbers](https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/)

## 题目

Given an integer `n`, return *the **decimal value** of the binary string formed by concatenating the binary representations of* `1` *to* `n` *in order, **modulo*** `109 + 7`.

 

**Example 1:**

```
Input: n = 1
Output: 1
Explanation: "1" in binary corresponds to the decimal value 1. 
```

**Example 2:**

```
Input: n = 3
Output: 27
Explanation: In binary, 1, 2, and 3 corresponds to "1", "10", and "11".
After concatenating them, we have "11011", which corresponds to the decimal value 27.
```

**Example 3:**

```
Input: n = 12
Output: 505379714
Explanation: The concatenation results in "1101110010111011110001001101010111100".
The decimal value of that is 118505380540.
After modulo 109 + 7, the result is 505379714.
```

 

**Constraints:**

- `1 <= n <= 10^5`

## 题目大意

给你一个整数 n ，请你将 1 到 n 的二进制表示连接起来，并返回连接结果对应的 十进制 数字对 10^9 + 7 取余的结果。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/concatenation-of-consecutive-binary-numbers/solution/lian-jie-lian-xu-er-jin-zhi-shu-zi-by-ze-t40j/)

### Solution 1: 模拟

这道题目如果用模拟的思路来做的话，不难想到想将 i 的十进制数，转化为 二进制表示形式，然后拼接后再转化为 十进制，

但是这里其实可以做一个优化，即不显式的进行转化到二进制这一步，直接在 十进制 层面来解决问题，

这里找到整个过程中的一个状态来进行分析，如果当前的数为 i，且已经对 [1, i - 1] 这个范围的数做了计算，且得到了对应的十进制表示形式，那么现在要解决的问题就是，如何将 i 加进去，这样问题就可以递推的来计算了

根据题目给的几个例子（想不出来动手模拟一下），想要将 i 加入到结果中，需要经 [1, i - 1] 的结果左移 i 的二进制位数，那么问题就转移到了如果来确定 i 的二进制位数，

这道题目还有一个条件即 范围是 [1, n]，所以相邻的两个数相差必为 1，所以 i 的长度要命与 i - 1 相同，要么比 i 更长，而且只有当 i 是 2 的整数次幂的时候，才会增加位数，所以问题就可以转移到确定 i 是否是 2 的整数次幂


````c++
class Solution {
public:
    int concatenatedBinary(int n) {
        int ans = 0;
        int shift = 0;
        for (int i = 1; i <= n; ++i) {
            if (!(i & (i - 1))) {
                ++shift;
            }
            ans = ((static_cast<long long>(ans) << shift) + i) % mod_;
        }
        return ans;
    }
    
 private:
    static const int mod_ = 1e9 + 7;
};
````


