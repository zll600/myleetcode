# [995. Minimum Number of K Consecutive Bit Flips](https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/)

## 题目

You are given a binary array `nums` and an integer `k`.

A **k-bit flip** is choosing a **subarray** of length `k` from `nums` and simultaneously changing every `0` in the subarray to `1`, and every `1` in the subarray to `0`.

Return *the minimum number of **k-bit flips** required so that there is no* `0` *in the array*. If it is not possible, return `-1`.

A **subarray** is a **contiguous** part of an array.

 

**Example 1:**

```
Input: nums = [0,1,0], k = 1
Output: 2
Explanation: Flip nums[0], then flip nums[2].
```

**Example 2:**

```
Input: nums = [1,1,0], k = 2
Output: -1
Explanation: No matter how we flip subarrays of size 2, we cannot make the array become [1,1,1].
```

**Example 3:**

```
Input: nums = [0,0,0,1,0,1,1,0], k = 3
Output: 3
Explanation: 
Flip nums[0],nums[1],nums[2]: nums becomes [1,1,1,1,0,1,1,0]
Flip nums[4],nums[5],nums[6]: nums becomes [1,1,1,1,1,0,0,0]
Flip nums[5],nums[6],nums[7]: nums becomes [1,1,1,1,1,1,1,1]
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `1 <= k <= nums.length`

## 题目大意

在仅包含 `0` 和 `1` 的数组 `nums` 中，

一次 `k` 位翻转包括选择一个长度为 `k` 的（连续）子数组，同时将子数组中的每个 `0` 更改为 `1`，而每个 `1` 更改为 `0`

返回所需的 `k` 位翻转的次数，以便数组没有值为 `0` 的元素。如果不可能，返回 -1。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/solution/hua-dong-chuang-kou-shi-ben-ti-zui-rong-z403l/)

### Solution 1: Brute force

这种解法按照是根据以下几点：

- 反转后面的不会影响前面的结果，
- nums[i] 反转 偶数次是它本身，反转奇数次就是 nums[i] ^ 1

`````python3
class Solution:
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        n = len(nums)
        cnt = 0
        # 从每个值为 0 的位置开始将 k 个数进行反转
        for i in range(n - k + 1):
            if nums[i] & 1 == 1:
                continue

            # print(f"{nums[i]}")
            for j in range(k):
                nums[i + j] ^= 1
            cnt += 1

        for i in range(n):
            if not nums[i] & 1:
                return -1
        return cnt
`````

### Solution 2: Sliding window

这里利用滑动窗口来存储每个需要反转的位置，

这里利用的思想还是暴力解法中的两个结论，优化的地方在于，在这里没有真的做反转，只是记录下需要反转的位置，如果这个位置不受上一下反转的影响，那么就需要增加反转的次数

````Python3
class Solution:
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        n = len(nums)
        # 这里利用 deque 来存储需要反转的位置
        que = collections.deque()
        cnt = 0
        for i in range(n):
            # 如果队列不为空，且已经不再受 que[0] 位置反转的影响了
            if que and i >= que[0] + k:
                que.popleft()
            # 如果需要反转
            if len(que) % 2 == nums[i]:
                # 不可能符合题意了
                if i + k > n:
                    return -1
                que.append(i)
                cnt += 1

        return cnt
````
