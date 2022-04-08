# [775. Global and Local Inversions](https://leetcode.com/problems/global-and-local-inversions/)

## 题目大意

You are given an integer array `nums` of length `n` which represents a permutation of all the integers in the range `[0, n - 1]`.

The number of **global inversions** is the number of the different pairs `(i, j)` where:

- `0 <= i < j < n`
- `nums[i] > nums[j]`

The number of **local inversions** is the number of indices `i` where:

- `0 <= i < n - 1`
- `nums[i] > nums[i + 1]`

Return `true` *if the number of **global inversions** is equal to the number of **local inversions***.

 

**Example 1:**

```
Input: nums = [1,0,2]
Output: true
Explanation: There is 1 global inversion and 1 local inversion.
```

**Example 2:**

```
Input: nums = [1,2,0]
Output: false
Explanation: There are 2 global inversions and 1 local inversion.
```

 

**Constraints:**

- `n == nums.length`
- `1 <= n <= 105`
- `0 <= nums[i] < n`
- All the integers of `nums` are **unique**.
- `nums` is a permutation of all the numbers in the range `[0, n - 1]`.

## 解题思路

给定一个整数数组 `nums` 和一个长度 `n`，其表示范围 `[0, n - 1]` 的一种排列

全局倒置指的是 `i,j` 满足 `0 <= i < j < N` 并且 `A[i] > A[j]` ，

局部倒置指的是 `i` 满足 `0 <= i < N` 并且 `A[i] > A[i+1]` 。

当数组 `A` 中 *全局倒置* 的数量等于 *局部倒置* 的数量时，返回 true 。

## 解题思路

分析题目，可以发现，局部倒置也属于全局倒置，所以要使得二者的总数相等，那么就不能出现非局部倒置的全局倒置

所以我们只要检测是否可能会出现非局部倒置的全局倒置即可

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/global-and-local-inversions/solution/775-cji-hu-shuang-bai-de-tan-xin-jie-fa-n9yh7/)

这里利用倒序遍历，遍历的过程中维护一个最小值，如果出现非局部倒置的全局倒置，直接返回 false 即可

````c++
class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        const int len = nums.size();
        // 倒序遍历，维护一个最小值
        int minmium = len;
        for (int i = len - 1; i >= 2; --i) {
            minmium = min(minmium, nums[i]);
            // 如果出现非局部倒置的全局倒置，直接返回 false
            if (nums[i - 2] > minmium) {
                return false;
            }
        }
        
        return true;
    }
};
````


