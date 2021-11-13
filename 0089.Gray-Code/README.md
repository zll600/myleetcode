# [89. Gray Code](https://leetcode.com/problems/gray-code/)

## 题目

An **n-bit gray code sequence** is a sequence of `2n` integers where:

- Every integer is in the **inclusive** range `[0, 2n - 1]`,
- The first integer is `0`,
- An integer appears **no more than once** in the sequence,
- The binary representation of every pair of **adjacent** integers differs by **exactly one bit**, and
- The binary representation of the **first** and **last** integers differs by **exactly one bit**.

Given an integer `n`, return *any valid **n-bit gray code sequence***.

 

**Example 1:**

```
Input: n = 2
Output: [0,1,3,2]
Explanation:
The binary representation of [0,1,3,2] is [00,01,11,10].
- 00 and 01 differ by one bit
- 01 and 11 differ by one bit
- 11 and 10 differ by one bit
- 10 and 00 differ by one bit
[0,2,3,1] is also a valid gray code sequence, whose binary representation is [00,10,11,01].
- 00 and 10 differ by one bit
- 10 and 11 differ by one bit
- 11 and 01 differ by one bit
- 01 and 00 differ by one bit
```

**Example 2:**

```
Input: n = 1
Output: [0,1]
```

 

**Constraints:**

- `1 <= n <= 16`

## 题目大意

**n 位格雷码序列** 是一个由 `2n` 个整数组成的序列，其中：

* 每个整数都在范围 [0, 2n - 1] 内（含 0 和 2n - 1）
* 第一个整数是 0
* 一个整数在序列中出现 不超过一次
* 每对 相邻 整数的二进制表示 恰好一位不同 ，且
  第一个 和 最后一个 整数的二进制表示 恰好一位不同

## 解题思路

这道题目可以看作每次增加一位，然后去从上一种状态开始求解，所以有一种方法就是利用动态规划来做

### Solutio 1:(DP)

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/gray-code/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by--12/

我们可以从 1 位出发，开始递推，来求解更多的位

````c++
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> dp;
        dp.push_back(0);
        
        for (int i = 0; i < n; ++i) {
            int incr = 1 << i;  // 要增加的大小
            // cout << incr << endl;
            
            // 倒序相加
            for (int j = dp.size() - 1; j >= 0; --j) {
                dp.push_back(dp[j] + incr);
            }
        }
        
        return dp;
    }
};
````

