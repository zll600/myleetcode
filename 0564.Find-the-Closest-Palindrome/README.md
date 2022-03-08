# [564. Find the Closest Palindrome](https://leetcode-cn.com/problems/find-the-closest-palindrome/)

## 题目

Given a string `n` representing an integer, return *the closest integer (not including itself), which is a palindrome*. If there is a tie, return ***the smaller one***.

The closest is defined as the absolute difference minimized between two integers.

 

**Example 1:**

```
Input: n = "123"
Output: "121"
```

**Example 2:**

```
Input: n = "1"
Output: "0"
Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.
```

 

**Constraints:**

- `1 <= n.length <= 18`
- `n` consists of only digits.
- `n` does not have leading zeros.
- `n` is representing an integer in the range `[1, 1018 - 1]`.

## 题目大意

给定一个表示整数的字符串 `n` ，返回与它最近的回文整数（不包括自身）。如果不止一个，返回较小的那个

“最近的”定义为两个整数差的绝对值最小

## 解题思路

如果使用暴力解法，就是枚举所有可能的数，判断每一个数是否是回文数

### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/find-the-closest-palindrome/solution/gong-shui-san-xie-tan-xin-fen-xi-shang-x-vtr6/)

这里我们利用每个数的前半部分，生成整个回文数，

````c++
class Solution {
public:
    string nearestPalindromic(string n) {
        const int len = n.size();
        // 原来的数
        long num = stol(n);
        // 所有可能匹配的结果
        unordered_set<long> cache;
        
        // 边界
        cache.insert(static_cast<long>(pow(10, (len - 1))) - 1);
        cache.insert(static_cast<long>(pow(10, len)) + 1);
        
        // 前几位
        long target = stol(n.substr(0, (len + 1) / 2));
        for (long i = target - 1; i <= target + 1; ++i) {
            // 这里我们要注意判断奇偶
            long palindrome = GetNum(i, len % 2 == 0);
            if (palindrome != num) {
                cache.insert(palindrome);
            }
        }
        
        long ans = -1;
        for (long item : cache) {
            // 1. 如果没有初始化
            // 2. 如果离 num 更近
            // 3. 如果值更小
            if (ans == -1
                || (abs(item - num) < abs(ans - num))
                || (abs(item - num) == abs(ans - num) && item < ans)) {
                ans = item;
            }
        }
        
        return to_string(ans);
    }
    
 private:
    // 生成一个回文数
    long GetNum(long num, bool is_even) {
        string str = to_string(num);
        const int len = str.size();
        // 根据奇偶来判断从那里开始指定生成
        int idx = is_even ? len - 1 : len - 2;
        
        // 用高位生成地位
        while (idx >= 0) {
            str.append(1, str[idx]);
            --idx;
        }
        
        return str.size() > 19 ? -1 : stol(str);
    }
};
````

