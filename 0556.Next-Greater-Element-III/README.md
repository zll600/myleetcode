# [556. Next Greater Element III](https://leetcode-cn.com/problems/next-greater-element-iii/)

Given a positive integer `n`, find *the smallest integer which has exactly the same digits existing in the integer* `n` *and is greater in value than* `n`. If no such positive integer exists, return `-1`.

**Note** that the returned integer should fit in **32-bit integer**, if there is a valid answer but it does not fit in **32-bit integer**, return `-1`.

 

**Example 1:**

```
Input: n = 12
Output: 21
```

**Example 2:**

```
Input: n = 21
Output: -1
```

 

**Constraints:**

- `1 <= n <= 231 - 1`

## 题目大意

给你一个正整数 n ，请你找出符合条件的最小整数，其由重新排列 n 中存在的每位数字组成，并且其值大于 n 。如果不存在这样的正整数，则返回 -1 。

注意 ，返回的整数应当是一个 32 位整数 ，如果存在满足题意的答案，但不是 32 位整数 ，同样返回 -1 。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/next-greater-element-iii/solution/cchao-100de-shu-xue-jie-fa-by-ffreturn-rccw/)

### Solution 1:



````c++
class Solution {
public:
    int nextGreaterElement(int n) {
        string num = to_string(n);
        const int len = num.size();
        
        if (len <= 1) {
            return -1;
        }
        
        int i = len - 2;
        while (i >= 0) {
            if (num[i] < num[i + 1]) {
                // 找到第一组降序的
                break;
            }
            --i;
        }
        
        if (i < 0) {
            // 如果没有，说明已经是最大的了，直接返回 -1，
            return -1;
        }
        
        int j = len - 1;
        while (j > i) {
            if (num[j] > num[i]) {
                // 找到第一个大于 num[i] 的
                break;
            }
            --j;
        }
        // 交换
        swap(num[i], num[j]);
        // 将其他地方逆序
        reverse(num.begin() + i + 1, num.end());
        
        // 这里是为了避免溢出
        long res = stol(num);
        return res > INT_MAX ? -1 : res;
    }
};
````




