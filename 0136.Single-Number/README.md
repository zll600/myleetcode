# [136. Single Number](https://leetcode.com/problems/single-number/)

## 题目

Given a **non-empty** array of integers `nums`, every element appears *twice* except for one. Find that single one.

You must implement a solution with a linear runtime complexity and use only constant extra space.

 

**Example 1:**

```
Input: nums = [2,2,1]
Output: 1
```

**Example 2:**

```
Input: nums = [4,1,2,1,2]
Output: 4
```

**Example 3:**

```
Input: nums = [1]
Output: 1
```

 

**Constraints:**

- `1 <= nums.length <= 3 * 104`
- `-3 * 104 <= nums[i] <= 3 * 104`
- Each element in the array appears twice except for one element which appears only once.

## 题目大意

给定一个非空的整数数组，除了某个元素出现一次外，其他数都出现了两次，找出那个数，

你必须实现一个解决方法在线性时间内的复杂度，使用常数空间

## 解题思路

* 这道题目可以利用异或的性质来做，只有一个数出现了一次，其余数出现了两次，我们可以利用一个数和他本身异或的结果为0，球的只出现了一次的数
* 这道题目其实可以扩展，除一个数之外其他数均出现了偶数次，方法是一样的。

## 代码

````c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        
        for (int num : nums) {
            res ^= num;
        }
        
        return res;
    }
};
````

