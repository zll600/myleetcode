# [866. Prime Palindrome](https://leetcode.cn/problems/prime-palindrome/)

## 题目

Given an integer n, return *the smallest **prime palindrome** greater than or equal to* `n`.

An integer is **prime** if it has exactly two divisors: `1` and itself. Note that `1` is not a prime number.

- For example, `2`, `3`, `5`, `7`, `11`, and `13` are all primes.

An integer is a **palindrome** if it reads the same from left to right as it does from right to left.

- For example, `101` and `12321` are palindromes.

The test cases are generated so that the answer always exists and is in the range `[2, 2 * 108]`.

 

**Example 1:**

```
Input: n = 6
Output: 7
```

**Example 2:**

```
Input: n = 8
Output: 11
```

**Example 3:**

```
Input: n = 13
Output: 101
```

 

**Constraints:**

- `1 <= n <= 108`

## 题目大意

求出大于或等于 `N` 的最小回文素数

回顾一下，如果一个数大于 1，且其因数只有 1 和它自身，那么这个数是素数

例如，2，3，5，7，11 以及 13 是素数

回顾一下，如果一个数从左往右读与从右往左读是一样的，那么这个数是回文数

例如，`12321` 是回文数

## 解题思路

这道题目的暴力解法就是由 n 开始递增，同时判断回文和判断素数

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/prime-palindrome/solution/fan-zhuan-xian-pan-duan-hui-wen-chuan-he-i07q/)

这中解法使用的优化就是构造回文，然后判断是否是素数

````c++
class Solution {
public:
    int primePalindrome(int n) {
        while (true) {
            string num_str = to_string(n);
            const int len = num_str.size();
            string after = num_str.substr(0, len / 2);
            reverse(after.begin(), after.end());
            string palindrome_str = num_str.substr(0, len - len / 2) + after;
            int palindrome_num = stoi(palindrome_str);

            if (palindrome_num >= n && IsPrime(palindrome_num)) {
                return palindrome_num;
            } else {
                string increase_str = num_str.substr(0, (len + 1) / 2);
                int increase_num = stoi(increase_str);
                ++increase_num;
                increase_str = to_string(increase_num);
                string increase_str_half = increase_str.substr(0, len / 2);
                reverse(increase_str_half.begin(), increase_str_half.end());
                palindrome_str = increase_str + increase_str_half;
                palindrome_num = stoi(palindrome_str);
                // cout << "2: " << palindrome_num << endl;
                if (palindrome_num >= n && IsPrime(palindrome_num)) {
                    return palindrome_num;
                }
            }
            n = palindrome_num;
        }
        return -1;
    }

 private:
    bool IsPrime(const int num) {
        if (num < 2) {
            return false;
        }

        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
};
````

