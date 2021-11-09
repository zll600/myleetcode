# [977. Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/)

## 题目

Given an integer array `nums` sorted in **non-decreasing** order, return *an array of **the squares of each number** sorted in non-decreasing order*.

 

**Example 1:**

```
Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].
```

**Example 2:**

```
Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-104 <= nums[i] <= 104`
- `nums` is sorted in **non-decreasing** order.

 

**Follow up:** Squaring each element and sorting the new array is very trivial, could you find an `O(n)` solution using a different approach?

## 题目大意

给定一个按照非递减顺序排序的整数数组，返回按照非递减排序的每个数的平方的数组

## 解题思路

题目中给出的初始序列是有序的，利用这一点，可以较好的解决这道题目

### Solution 1:

这道题目最简单的解法，就是直接求出所有数的平方，然后重新排序，不过这种解法并没有利用数组有序的特征

````c++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        const int len = nums.size();
        // 分别求平方
        for_each(nums.begin(), nums.end(), [](int& num){
            num *= num;
        });
        
        // 排序
        sort(nums.begin(), nums.end());
        
        return nums;
    }
};
````

### Solution 2:

理论上这种解法应该是可以过的，但是leetcode 给的数据超范围了，利用原数组的有序性，每次最大值，一定是从数组的两端求得

````c++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        const int len = nums.size();
        // 每次酱最大的放在最后一个位置上，
        for (int i = len - 1, first = 0, last = len - 1; first <= last; --i) {
            if (1L * nums[last] * nums[last] > 1L * nums[first] * nums[first]) {
                nums[i] = nums[last] * nums[last];
                --last;
            } else {
                nums[i] = nums[first] * nums[first];
                ++first;
            }
        }
        
        return nums;
    }
};
````

