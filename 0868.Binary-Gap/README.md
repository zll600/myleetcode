# [868. Binary Gap](https://leetcode-cn.com/problems/binary-gap/)

## 题目

Given a positive integer `n`, find and return *the **longest distance** between any two **adjacent*** `1`*'s in the binary representation of* `n`*. If there are no two adjacent* `1`*'s, return* `0`*.*

Two `1`'s are **adjacent** if there are only `0`'s separating them (possibly no `0`'s). The **distance** between two `1`'s is the absolute difference between their bit positions. For example, the two `1`'s in `"1001"` have a distance of 3.

 

**Example 1:**

```
Input: n = 22
Output: 2
Explanation: 22 in binary is "10110".
The first adjacent pair of 1's is "10110" with a distance of 2.
The second adjacent pair of 1's is "10110" with a distance of 1.
The answer is the largest of these two distances, which is 2.
Note that "10110" is not a valid pair since there is a 1 separating the two 1's underlined.
```

**Example 2:**

```
Input: n = 8
Output: 0
Explanation: 8 in binary is "1000".
There are not any adjacent pairs of 1's in the binary representation of 8, so we return 0.
```

**Example 3:**

```
Input: n = 5
Output: 2
Explanation: 5 in binary is "101".
```

 

**Constraints:**

- `1 <= n <= 109`

## 题目大意

给定一个正整数 n，返回 n 的二进制表示中距离最远的相邻的两个 1，如果没有两个相邻的 1，返回 0。

如果只有 0 将两个 1 分隔开（可能没有 0），则认为这两个 1 是相邻的，两个 1 之间的距离，是它们位表示的绝对距离，

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/binary-gap/solution/wei-yun-suan-chao-100-c-by-zhouzihong-x55c/

这是一道位运算的题目

### Solution 1:

这种解法需要注意的是像 8，12 这种数字，刚开始出现的多个连续的 0  并不能直接用，这里的解决方法是统计 1 出现的次数来做，其实题解中的做法更好，设初值为负，可以解决这个问题，

````c++
class Solution {
public:
    int binaryGap(int n) {
        int res = 0; // 结果
        int dis = 0; // 更新距离
        int cnt = 0; // 统计 1 的数目
        while (n) {
            // 这里做的相当于倒序遍历
            int bit = (n & 1); // 取最低位
            if (bit == 0) {
                // 如果是 0
                ++dis;
            } else if (bit == 1) {
                // 如果是 1
                if (cnt > 0) {
                    res = max(res, dis);
                }
                dis = 1;
                ++cnt;
            }
            n >>= 1; // 左移一位
        }
        
        return cnt > 1 ? res : 0;
    }
};
````

### Solution 2:

```c++
class Solution {
public:
    int binaryGap(int n) {
        int res = INT_MIN; // 结果
        int dis = INT_MIN; // 更新距离
        while (n) {
            // 这里做的相当于倒序遍历
            int bit = (n & 1); // 取最低位
            if (bit == 0) {
                // 如果是 0
                ++dis;
            } else if (bit == 1) {
                // 如果是 1
                res = max(res, dis);
                dis = 1;
            }
            n >>= 1; // 左移一位
        }
        
        return res > 0 ? res : 0;
    }
};
```

