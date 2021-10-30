# [368. Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)

##

Given a set of **distinct** positive integers `nums`, return the largest subset `answer` such that every pair `(answer[i], answer[j])` of elements in this subset satisfies:

- `answer[i] % answer[j] == 0`, or
- `answer[j] % answer[i] == 0`

If there are multiple solutions, return any of them.

 

**Example 1:**

```
Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.
```

**Example 2:**

```
Input: nums = [1,2,4,8]
Output: [1,2,4,8]
```

 

**Constraints:**

- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 2 * 109`
- All the integers in `nums` are **unique**.

##

给定一族不同的正整数 nums，返回最大的子集 answer，其中每对(answer[i], answer[j]) 中的元素都满足

* answer[i] % answer[j] == 0 或
* answer[j] % answer[i] == 0

如果有多个解，返回其中任意的