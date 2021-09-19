# [137. Single Number II](https://leetcode.com/problems/single-number-ii/)

## 题目

Given an integer array `nums` where every element appears **three times** except for one, which appears **exactly once**. *Find the single element and return it*.

You must implement a solution with a linear runtime complexity and use only constant extra space.

 

**Example 1:**

```
Input: nums = [2,2,3,2]
Output: 3
```

**Example 2:**

```
Input: nums = [0,1,0,1,0,1,99]
Output: 99
```

 

**Constraints:**

- `1 <= nums.length <= 3 * 104`
- `-231 <= nums[i] <= 231 - 1`
- Each element in `nums` appears exactly **three times** except for one element which appears **once**.

## 题目大意

给定一个数组，除了一个数之外，数组中的每个数出现了三次，找出只出现了一次的数，

你必须在线性的时间复杂度和常数空间内解决问题

## 解题思路

* 这道题目是136 题的升级版，这里可以参考这篇题解：https://leetcode-cn.com/problems/single-number-ii/solution/single-number-ii-mo-ni-san-jin-zhi-fa-by-jin407891/
* 对于出现3次的数，其二进制上的各位的 1 出现的次数均为 3，统计所有数中二进制位上的 1 出现的次数，然后对 3 取余，最终剩下的就是只出现了一次的数。
* 这道题目目前只实现了最简单直接的方法，此外还有很多高阶的解法，留待以后实现，这道题目将 3 改为其他的数字，也可以应用

## 代码

````c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> count(32);
        
        for (int num : nums) {  // 对每一个数进行统计
            for (int i = 0; i < 32; ++i) {
                count[i] += (num & 1); // 统计但前数的第 i 位的值
                num >>= 1;  // 准备计算下一位
            }
        }
        
        // for (int& num : count) {
        //     num %= 3;
        // }
        
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            res <<= 1;  // 准备对下一位进行操作
            res |= count[31 - i] % 3;   // 这里对 3 取余
        }
        
        return res;
    }
};
````



