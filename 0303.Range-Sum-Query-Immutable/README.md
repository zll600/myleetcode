# [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)

## 题目

Given an integer array `nums`, handle multiple queries of the following type:

1. Calculate the **sum** of the elements of `nums` between indices `left` and `right` **inclusive** where `left <= right`.

Implement the `NumArray` class:

- `NumArray(int[] nums)` Initializes the object with the integer array `nums`.
- `int sumRange(int left, int right)` Returns the **sum** of the elements of `nums` between indices `left` and `right` **inclusive** (i.e. `nums[left] + nums[left + 1] + ... + nums[right]`).

 

**Example 1:**

```
Input
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
Output
[null, 1, -1, -3]

Explanation
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `-105 <= nums[i] <= 105`
- `0 <= left <= right < nums.length`
- At most `104` calls will be made to `sumRange`.

## 题目大意

给定一个整数数组，计算给定索引范围内元素之和，包含 i，和 J，两个位置

## 解题思路

* 这是一道前缀和的题目，利用前缀和，可以很好的做到空间换时间，
* 前缀和本质是利用数学进行求值：某一段的区间和 = 起点到区间右端点的和（含右端点） - 起点到区间左端点的和（不含左端点），
* 求解前缀和数组的过程利用的是动态规划的思想，`当前位置的前缀和 = 前一个位置的前缀和 + 当前位置的值（而与前一个位置是则怎么计算出来的没有关系）`

## 代码

````c++
class NumArray {
public:
    NumArray(vector<int>& nums) {
        int size = nums.size();
        sum.reserve(size + 1);
        for (int i = 1; i <= size; ++i) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
    }
    
    int sumRange(int left, int right) {
        return sum[++right] - sum[++left - 1];
    }
    
 private:
    vector<int> sum;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
````

