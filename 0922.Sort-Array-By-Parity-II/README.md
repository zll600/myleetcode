# [922. Sort Array By Parity II](https://leetcode.com/problems/sort-array-by-parity-ii/)

## 题目

Given an array of integers `nums`, half of the integers in `nums` are **odd**, and the other half are **even**.

Sort the array so that whenever `nums[i]` is odd, `i` is **odd**, and whenever `nums[i]` is even, `i` is **even**.

Return *any answer array that satisfies this condition*.

 

**Example 1:**

```
Input: nums = [4,2,5,7]
Output: [4,5,2,7]
Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.
```

**Example 2:**

```
Input: nums = [2,3]
Output: [2,3]
```

 

**Constraints:**

- `2 <= nums.length <= 2 * 104`
- `nums.length` is even.
- Half of the integers in `nums` are even.
- `0 <= nums[i] <= 1000`

 

**Follow Up:** Could you solve it in-place?

## 题目大意

要求数组中奇数下标位置上放奇数，偶数下标位置上放偶数

## 解题思路


### Solution 1:

这种解法比较简单，按照题意即可

````c++
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int odd_idx = 1;
        int even_idx = 0;

        const int len = nums.size();
        vector<int> res(len, 0);
        for (int num : nums) {
            if (num % 2 == 0) {
                res[even_idx] = num;
                even_idx += 2;
            } else {
                res[odd_idx] = num;
                odd_idx += 2;
            }
        }

        return res;
    }
};
````
