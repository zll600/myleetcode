# [1695. Maximum Erasure Value](https://leetcode.com/problems/maximum-erasure-value/)

## 题目

You are given an array of positive integers `nums` and want to erase a subarray containing **unique elements**. The **score** you get by erasing the subarray is equal to the **sum** of its elements.

Return *the **maximum score** you can get by erasing **exactly one** subarray.*

An array `b` is called to be a subarray of `a` if it forms a contiguous subsequence of `a`, that is, if it is equal to `a[l],a[l+1],...,a[r]` for some `(l,r)`.

 

**Example 1:**

```
Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].
```

**Example 2:**

```
Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 104`

## 题目大意

给定一个正整数数组 nums，删除一个不含重复数字的子数组，删除则各数组得到的得分是这个子数组的和，

返回你删除一个子数组可以得到的最大得分

如果数组 `b` 是数组 `a` 的一个连续子序列，即如果它等于 `a[l],a[l+1],...,a[r]` ，那么它就是 `a` 的一个子数组。

### 解题思路

子数组的累加和问题，显然可以使用滑动窗口来解决，可以避免使用嵌套循环

#### Solution 1：

````c++
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int left = 0;  // 左边界
        int right = 0;  // 右边界
        int res = 0;  // 结果
        int sum = 0;  // 累加和
        unordered_set<int> ht;  // 记录是否出现过

        const int size = nums.size();
        // 循环不变量 [left, right] 表示窗口
        while (right < size) {
            if (ht.find(nums[right]) == ht.end()) {  // 如果不存在
                sum += nums[right];  // 累加
                res = max(res, sum);  // 更新结果
                ht.emplace(nums[right]);  // 添加
                ++right;  // 扩大右边界
            } else {
                while (ht.find(nums[right]) != ht.end()) {  // 缩小左边界直到不重复为止
                    sum -= nums[left];  // 除去
                    ht.erase(nums[left]);  // 删除
                    ++left;  // 缩小左边界
                }
            }
        }

        return res;
    }
};c
````

### Solution 2:

花花酱的解法

````c++
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        const int size = nums.size();
        unordered_set<int> ht;

        int res = 0;
        for (int left = 0, right = 0, sum = 0; right < size; ++right) {
            // 如果出现重复，而且窗口正常，则缩小左边界，直至消除重复
            while (ht.find(nums[right]) != ht.end() && left < right) {
                sum -= nums[left];
                ht.erase(nums[left++]);
            }
            ht.insert(nums[right]);  // 记录
            sum += nums[right];  // 累加
            res = max(res, sum);  // 更新
        }

        return res;
    }
};
````

