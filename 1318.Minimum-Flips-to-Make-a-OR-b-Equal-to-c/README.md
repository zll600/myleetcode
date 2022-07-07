#### [1318. Minimum Flips to Make a OR b Equal to c](https://leetcode.cn/problems/minimum-flips-to-make-a-or-b-equal-to-c/)

Given 3 positives numbers `a`, `b` and `c`. Return the minimum flips required in some bits of `a` and `b` to make ( `a` OR `b` == `c` ). (bitwise OR operation).
 Flip operation consists of change **any** single bit 1 to 0 or change the bit 0 to 1 in their binary representation.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/01/06/sample_3_1676.png)

```
Input: a = 2, b = 6, c = 5
Output: 3
Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
```

**Example 2:**

```
Input: a = 4, b = 2, c = 7
Output: 1
```

**Example 3:**

```
Input: a = 1, b = 2, c = 3
Output: 0
```

 

**Constraints:**

- `1 <= a <= 10^9`
- `1 <= b <= 10^9`
- `1 <= c <= 10^9`



### Solution 1: Bit manipluation

这种解法可以参考这篇 [题解](https://leetcode.cn/problems/minimum-flips-to-make-a-or-b-equal-to-c/solution/qing-xi-jian-dan-you-qu-de-tui-li-yan-suan-by-hlxi/)

其实这道题目最先想到是的线性 `dp`，但是这道题目有一个特点就是，每一位反转两次后不变

这道题目主要考察的是位运算的知识

````c++
class Solution {
public:
    int minFlips(int a, int b, int c) {
        int ans = 0;
        
        while (a || b || c) {
            int av = a & 1, bv = b & 1, cv = c & 1;
            a >>= 1;
            b >>= 1;
            c >>= 1;
            
            if ((av | bv) == cv) {
                continue;
            }
            
            if ((av | bv) == 1 && cv == 0) {
                // if av == 1, flip av
                if (av == 1) {
                    ++ans;
                }
                // if bv == 1 flip bv
                if (bv == 1) {
                    ++ans;
                }
            } else if ((av | bv) == 0 && cv == 1) {
                // flip av or bv
                ans += 1;
            }
        }
        return ans;
    }
};
````



