# [905. Sort Array By Parity](https://leetcode-cn.com/problems/sort-array-by-parity/)

## 题目

Given an integer array `nums`, move all the even integers at the beginning of the array followed by all the odd integers.

Return ***any array** that satisfies this condition*.

 

**Example 1:**

```
Input: nums = [3,1,2,4]
Output: [2,4,3,1]
Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
```

**Example 2:**

```
Input: nums = [0]
Output: [0]
```

 

**Constraints:**

- `1 <= nums.length <= 5000`
- `0 <= nums[i] <= 5000`

## 题目大意

给定一个整数数组 nums，将所有的奇数元素放在偶数元素的后面

## 解题思路

### Solution 1: In place

直接原地修改

````c++
class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int size = A.size();
        int left = 0, right = size - 1;
        
        while (left <= right) {
            if (A[left] % 2 != 0 && A[right] % 2 == 0) {  // 需要交换
                swap(A[left], A[right]);
                ++left;
                --right;
            } else if (A[left] % 2 == 0) {  // 不需要交换
                ++left;
            } else if (A[right] % 2 != 0) {  // 不需要交换
                --right;
            }
        }
        
        return A;
    }
};
````

