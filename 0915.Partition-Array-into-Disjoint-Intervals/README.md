# [915. Partition Array into Disjoint Intervals](https://leetcode.cn/problems/partition-array-into-disjoint-intervals/)

## 题目

Given an integer array `nums`, partition it into two (contiguous) subarrays `left` and `right` so that:

- Every element in `left` is less than or equal to every element in `right`.
- `left` and `right` are non-empty.
- `left` has the smallest possible size.

Return *the length of* `left` *after such a partitioning*.

Test cases are generated such that partitioning exists.

 

**Example 1:**

```
Input: nums = [5,0,3,8,6]
Output: 3
Explanation: left = [5,0,3], right = [8,6]
```

**Example 2:**

```
Input: nums = [1,1,1,0,6,12]
Output: 4
Explanation: left = [1,1,1,0], right = [6,12]
```

 

**Constraints:**

- `2 <= nums.length <= 105`
- `0 <= nums[i] <= 106`
- There is at least one valid answer for the given input.

## 题目大意

给定一个数组 `nums` ，将其划分为两个连续子数组 `left` 和 `right`， 使得：

-   left 中的每个元素都小于或等于 right 中的每个元素
-   left 和 right 都是非空的
-   left 的长度要尽可能小

在完成这样的分组后返回 left 的 长度

用例可以保证存在这样的划分方法

## 解题思路

在遍历数组的过程中，需要一直更新左边的最大值 `left_max`，同时维护整个遍历过程的最大值 `max_value`，

遇到的下一个数为 `nums[i]`

- `nums[i] < left_max` 那么说明需要将 `nums[i]` 加入到左边才可以
- `nums[i] >= left_max` 说明不需要改变左边

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/partition-array-into-disjoint-intervals/solution/)

````c++
class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        const int len = nums.size();
        // [0...i] 中的最大值
        int max_value = nums[0];
        // [0, pos] 中最大的值
        int left_max = max_value;
        int pos = 0;
        for (int i = 1; i < len; ++i) {
            max_value = max(max_value, nums[i]);
            // 满足题意
            if (left_max <= nums[i]) {
                continue;
            }
            
            // 需要更新
            left_max = max_value;
            pos = i;
        }
        return pos + 1;
    }
};
````


