# [338. Counting Bits](https://leetcode.com/problems/counting-bits/)

Given an integer `n`, return *an array* `ans` *of length* `n + 1` *such that for each* `i` (`0 <= i <= n`)*,* `ans[i]` *is the **number of*** `1`***'s** in the binary representation of* `i`.

 

**Example 1:**

```
Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10
```

**Example 2:**

```
Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
```

 

**Constraints:**

- `0 <= n <= 105`

 

**Follow up:**

- It is very easy to come up with a solution with a runtime of `O(n log n)`. Can you do it in linear time `O(n)` and possibly in a single pass?
- Can you do it without using any built-in function (i.e., like `__builtin_popcount` in C++)?

## 题目大意

给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

## 解题思路

* 这道题目最清晰的解决办法是举例，然后找规律
  * 对于奇数：奇数中的1一定比它的前一个偶数多 1，也就是最低位的那个 1
  * 对于偶数：等价于将 前面的一个偶数左移，因此而二者的 1 的个数是一样的，只是做了一次移位操作，

## 代码

````c++
class Solution {
public:
    // 解法1：DP
    vector<int> countBits1(int n) {
        vector<int> res(n + 1);
        
        for (int i = 1; i <= n; ++i) {
            res[i] += res[i & (i - 1)] + 1;
        }
        
        return res;
    }
    
    // 解法二：     
    vector<int> countBits(int n) {
        vector<int> res(n + 1);
        res[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            if (i & 1) {
                res[i] = res[i - 1] + 1;
            } else {
                res[i] = res[i >> 1];
            }
        }
        
        return res;
    }
};
````

