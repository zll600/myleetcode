#### [1317. Convert Integer to the Sum of Two No-Zero Integers](https://leetcode.cn/problems/convert-integer-to-the-sum-of-two-no-zero-integers/)

## 题目

**No-Zero integer** is a positive integer that **does not contain any `0`** in its decimal representation.

Given an integer `n`, return *a list of two integers* `[A, B]` *where*:

- `A` and `B` are **No-Zero integers**.
- `A + B = n`

The test cases are generated so that there is at least one valid  solution. If there are many valid solutions you can return any of them.

 

**Example 1:**

```
Input: n = 2
Output: [1,1]
Explanation: A = 1, B = 1. A + B = n and both A and B do not contain any 0 in their decimal representation.
```

**Example 2:**

```
Input: n = 11
Output: [2,9]
```

 

**Constraints:**

- `2 <= n <= 104`

## 题目大意



## 解题思路



## Solution 1:

枚举所有 `[1, n / 2]` 的所有数，重点是 check 函数的编写，需要完成判断，数字中不含0

````c++
class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        vector<int> ans(2);
        for (int i = 1; i <= n / 2; ++i) {
            if (Check(i) && Check(n - i)) {
                ans[0] = i;
                ans[1] = n - i;
            }
        }
        return ans;
    }
    
 private:
    bool Check(int cur) {
        while (cur) {
            if (cur % 10 == 0) {
                return false;
            }
            cur /= 10;
        }
        return true;
    }
};
````

