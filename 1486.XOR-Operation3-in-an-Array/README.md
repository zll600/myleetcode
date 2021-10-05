# [1486. XOR Operation in an Array](https://leetcode.com/problems/xor-operation-in-an-array/)

Given an integer `n` and an integer `start`.

Define an array `nums` where `nums[i] = start + 2*i` (0-indexed) and `n == nums.length`.

Return the bitwise XOR of all elements of `nums`.

 

**Example 1:**

```
Input: n = 5, start = 0
Output: 8
Explanation: Array nums is equal to [0, 2, 4, 6, 8] where (0 ^ 2 ^ 4 ^ 6 ^ 8) = 8.
Where "^" corresponds to bitwise XOR operator.
```

**Example 2:**

```
Input: n = 4, start = 3
Output: 8
Explanation: Array nums is equal to [3, 5, 7, 9] where (3 ^ 5 ^ 7 ^ 9) = 8.
```

**Example 3:*

```
Input: n = 1, start = 7
Output: 7
```

**Example 4:**

```
Input: n = 10, start = 5
Output: 2
```

 

**Constraints:**

- `1 <= n <= 1000`
- `0 <= start <= 1000`
- `n == nums.length`

## 题目大意

给定一个整数 n 和一个整数 start，

定义一个数组 nums：其中 nums[i] = start + 2 * i（以 0 为下标索引）n为数组的长度

返回 nums 中所有元素异或之后得到的结果

## 解题思路

### 解法1（模拟）

这种方法就是根据题目的要求简单模拟去做

`````c++
class Solution {
public:
    int xorOperation(int n, int start) {
        int res = start;
        for (int i = 1; i< n; i++) {
            int cur = start + 2 * i;
            res ^= cur;
        }
        return res;
    }
};
`````

### 解法2（数学）

这道题目还有一种数学解法，不过我太菜了，不会

https://leetcode-cn.com/problems/xor-operation-in-an-array/solution/gong-shui-san-xie-yi-ti-shuang-jie-mo-ni-dggg/
