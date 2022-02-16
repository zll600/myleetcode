# [31. Next Permutation](https://leetcode-cn.com/problems/next-permutation/)

## 题目

A **permutation** of an array of integers is an arrangement of its members into a sequence or linear order.

- For example, for `arr = [1,2,3]`, the following are considered permutations of `arr`: `[1,2,3]`, `[1,3,2]`, `[3,1,2]`, `[2,3,1]`.

The **next permutation** of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the **next permutation** of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

- For example, the next permutation of `arr = [1,2,3]` is `[1,3,2]`.
- Similarly, the next permutation of `arr = [2,3,1]` is `[3,1,2]`.
- While the next permutation of `arr = [3,2,1]` is `[1,2,3]` because `[3,2,1]` does not have a lexicographical larger rearrangement.

Given an array of integers `nums`, *find the next permutation of* `nums`.

The replacement must be **[in place](http://en.wikipedia.org/wiki/In-place_algorithm)** and use only constant extra memory.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: [1,3,2]
```

**Example 2:**

```
Input: nums = [3,2,1]
Output: [1,2,3]
```

**Example 3:**

```
Input: nums = [1,1,5]
Output: [1,5,1]
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 100`

## 题目大意

一个整数数组的 **排列** 是指将其所有成员排成序列或者按照线性顺序排序，

- 举例来说，对于 `arr = [1,2,3]` 来说，接下来的排列是 `[1,2,3]`，`[1,3,2]`、`[3,1,2]`、`[2,3,1]`

整数数组的 **下一个排列** 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 **下一个排列** 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。
类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。
而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。

给你一个整数数组 nums ，找出 nums 的下一个排列。

必须 原地 修改，只允许使用额外常数空间。


## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/next-permutation/solution/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/)

### Solution 1:

以  `[1,3,2]` 为例
这种解法的步骤如下：
1. 从后向前遍历，找到第一组按照升序排序的数，`[1,3]`，则 `3` 后面的部分必定是降序的，
2. 从后向前遍历找到第一个比 `1` 大的数，这里是 `2`，然后交换位置
3. 将 `3` 之后的所有位变为升序，这里的话，直接逆序就好

````c++
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        const int len = nums.size();
        if (len == 1) {
            return;
        }

        int i = len - 2, j = len - 1, k = len - 1;

        // 找到第一组升序 nums[i] < nums[j]
        while (i >= 0 && nums[i] >= nums[j]) {
            --i;
            --j;
        }

        // 如果存在升序
        if (i >= 0) {
            // 找到第一个 比。nums[i] 大的数
            while (nums[i] >= nums[k]) {
                --k;
            }
            // 交换
            swap(nums[i], nums[k]);
        }

        // 将剩下的其余部分调整为升序
        reverse(nums.begin() + j, nums.end());
    }
};
````
