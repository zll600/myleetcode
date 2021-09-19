# [260. Single Number III](https://leetcode.com/problems/single-number-iii/) 

## 题目

Given an integer array `nums`, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in **any order**.

You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

 

**Example 1:**

```
Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.
```

**Example 2:**

```
Input: nums = [-1,0]
Output: [-1,0]
```

**Example 3:**

```
Input: nums = [0,1]
Output: [1,0]
```

 

**Constraints:**

- `2 <= nums.length <= 3 * 104`
- `-231 <= nums[i] <= 231 - 1`
- Each integer in `nums` will appear twice, only two integers will appear once.

## 题目大意

给定一个整数数组，有两个元素只出现了一次，其余都出现了两次，请找出那两个只出现了一次的数，

限定线性时间复杂度，和常数的空间内解决，

## 解题思路

* 这道题目可以先利用异或将出现两次的数消除，最后剩下的就是只出现一次的两个所数的异或，
* 取异或值的最后一个作为 mask，
* 再次遍历数组，两个出现一次的数，分别就是 异或 mask 为0 和异或 mask 为1，

## 代码

`````c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        long diff = 0;
        for (int num : nums) {
            diff ^= num;
        }
        
        diff &= -diff;  // 取得lsb(last set bit)，
        vector<int> res(2);
        for (int num : nums) {  // 在这里将两个数给分出来，
            if ((num & diff) == 0) {
                res[0] ^= num;
            } else {
                res[1] ^= num;
            }
        }
        
        return res;
    }
};
`````

