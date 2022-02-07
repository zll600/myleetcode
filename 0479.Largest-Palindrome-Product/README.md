# [479. Largest Palindrome Product](https://leetcode-cn.com/problems/largest-palindrome-product/)

## 题目

Given an integer n, return *the **largest palindromic integer** that can be represented as the product of two `n`-digits integers*. Since the answer can be very large, return it **modulo** `1337`.

 

**Example 1:**

```
Input: n = 2
Output: 987
Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
```

**Example 2:**

```
Input: n = 1
Output: 9
```

 

**Constraints:**

- `1 <= n <= 8`

## 题目大意

给定一个整数 n ，返回 可表示为两个 n 位整数乘积的 最大回文整数。因为答案可能非常大，所以返回它对 1337 取余 。

## 解题思路

这道题目我们要解决的问题有：

- 求最大的回文整数
- 怎样判断一个整数是不是回文整数
- 这个数要能够由 两个 n 为整数相乘得到，


### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/largest-palindrome-product/solution/9-line-in-java-by-wdw87/)

这种解法从大到小判断每个回文数是否可以由两个 n 位数相乘得到，这里是构造了两个回文数，所以不需要再额外判断回文

````c++
class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }
        
        long factor = std::pow(10, n) - 1; // 单个因数的最大值
        for (int i = factor - 1; i > factor / 10; --i) {
            string num = to_string(i);
            string tmp = num;
            reverse(tmp.begin(), tmp.end());
            
            long value = stol(num + tmp); // 得到回文数
            // 判断回文数能不能由两个数相乘得到
            for (long j = factor; j * j >= value; --j) {
                if (value % j == 0) {
                    return value % 1337;
                }
            }
        }
        
        return -1;
    }
    
 private:
    const int mod = 1337;
};
````
