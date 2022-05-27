# [2165. Smallest Value of the Rearranged Number](https://leetcode.com/problems/smallest-value-of-the-rearranged-number/)

## 题目

You are given an integer `num.` **Rearrange** the digits of `num` such that its value is **minimized** and it does not contain **any** leading zeros.

Return *the rearranged number with minimal value*.

Note that the sign of the number does not change after rearranging the digits.

 

**Example 1:**

```
Input: num = 310
Output: 103
Explanation: The possible arrangements for the digits of 310 are 013, 031, 103, 130, 301, 310. 
The arrangement with the smallest value that does not contain any leading zeros is 103.
```

**Example 2:**

```
Input: num = -7605
Output: -7650
Explanation: Some possible arrangements for the digits of -7605 are -7650, -6705, -5076, -0567.
The arrangement with the smallest value that does not contain any leading zeros is -7650.
```

 

**Constraints:**

- `-1015 <= num <= 1015`

## 题目大意

给你一个整数 `num` 。重排 `num` 中的各位数字，使其值 最小化 且不含 任何 前导零

返回不含前导零且值最小的重排数字。注意，重排各位数字后，num 的符号不会改变

## 解题思路

这道题目要考虑清楚正数和负数的不同情况，以及等于 0 的情况

### Solution 1:

`````c++
class Solution {
public:
    long long smallestNumber(long long num) {
        if (num == 0) {
            return 0;
        }

        // 转化为字符串形式，并排序
        string str = to_string(abs(num));
        sort(str.begin(), str.end());
        // 处理正数
        if (num > 0) {
            return Positive(str);
        }

        // 处理负数
        return -1 * Negative(str);
    }

 private:
    // 处理正数
    long long Positive(const string& str) {
        string ans = str;
        auto pos = str.find_first_not_of("0", 0);
        if (pos != string::npos) {
            swap(ans[0], ans[pos]);
        }
        return stoll(ans);
    }
    // 处理负数
    long long Negative(const string& str) {
        string ans = str;
        reverse(ans.begin(), ans.end());
        return stoll(ans);
    }
};
````
