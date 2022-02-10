# [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

## 题目

Given an integer array `nums` and an integer `k`, return *the length of the shortest non-empty **subarray** of* `nums` *with a sum of at least* `k`. If there is no such **subarray**, return `-1`.

A **subarray** is a **contiguous** part of an array.

 

**Example 1:**

```
Input: nums = [1], k = 1
Output: 1
```

**Example 2:**

```
Input: nums = [1,2], k = 4
Output: -1
```

**Example 3:**

```
Input: nums = [2,-1,2], k = 3
Output: 3
```

 

**Constraints:**

- `1 <= nums.length <= 105`
- `-105 <= nums[i] <= 105`
- `1 <= k <= 109`

## 题目大意

给定一个整数数组 nums 和一个整数 k，返回元素和至少为 k 的最短的非空子数组，如果不存在这样的子数组，返回 -1。

子数组是一个数组中连续的 部分

## 解题思路

这道题目涉及到了区间求和的问题，因此可以考虑使用滑动窗口来做，这里的难点在于这里的数是可以出现负数的，

这道题目可以参考这篇题解：https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0862.Shortest-Subarray-with-Sum-at-Least-K/

另外这类题目可以参考这篇题解：https://leetcode-cn.com/problems/unique-substrings-in-wraparound-string/solution/xi-fa-dai-ni-xue-suan-fa-yi-ci-gao-ding-qian-zhui-/



### Solution 1:

* 这道题目的难点在于数组中可能存在负数，所以累加和不会随着数组长度的增加而增加，题目中求区间和，这里可以使用前缀和来解决
* 求出 `nums` 的前缀和数组 `prefix`，`prefix[j] - prefix[i]` 表示 `nums[i] ~ nums[j - 1]` 的和，通过将这个值和 k 比较，来求得最小区间
* 在遍历数组的时候，使用了两个循环，
  * 第一个循环是因为，如果两个前缀和的下标可以靠的近一点，则子数组的长度就更短，
  * 第二个循环是为了维护 双向队列中的值是单调递增的，如果出现递减，则说明出现了负数，二出现负数，必然不是最短的子数组了，

````c++
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        const int len = nums.size();
        deque<int> idxes; // 这个队列用来存储下标
        int res = len; // 这里将结果初始化为最大值
        
        for (int i = 0; i < len; ++i) {
            if (i > 0) {
                // 这里使用原数组充当前缀和数组
                nums[i] += nums[i - 1];
            }
            if (nums[i] >= k) {
                // 如果此时的 前缀和 满足要求
                res = min(res, i + 1);
            }
            
            while (!idxes.empty() && nums[i] - nums[idxes.front()] >= k) {
                // 如果 i 到 idxes.front() 这一段满足要求
                res = min(res, i - idxes.front()); // 更新结果
                // 这里可以直接更新的原因是：
                // 即使后面的 前缀和值 满足要求，但是其构成的子数组也一定比当前的长，所以这里可以直接弹出
                idxes.pop_front();
            }
            while (!idxes.empty() && nums[i] <= nums[idxes.back()]) {
                // 这里也是为了让整个 deque 中下标对应的前缀和诚 递增的状态
                idxes.pop_back();
            }
            idxes.push_back(i);
        }
        return res;
    }
};
````

### Solution2:

上面的那个 c++ 版本暂时过不了，这里贴上大神的 [题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0862.Shortest-Subarray-with-Sum-at-Least-K/)

````go
func shortestSubarray(A []int, K int) int {
	res, prefixSum := len(A)+1, make([]int, len(A)+1)
	for i := 0; i < len(A); i++ {
		prefixSum[i+1] = prefixSum[i] + A[i]
	}
	// deque 中保存递增的 prefixSum 下标
	deque := []int{}
	for i := range prefixSum {
		// 下面这个循环希望能找到 [deque[0], i] 区间内累加和 >= K，如果找到了就更新答案
		for len(deque) > 0 && prefixSum[i]-prefixSum[deque[0]] >= K {
			length := i - deque[0]
			if res > length {
				res = length
			}
			// 找到第一个 deque[0] 能满足条件以后，就移除它，因为它是最短长度的子序列了
			deque = deque[1:]
		}
		// 下面这个循环希望能保证 prefixSum[deque[i]] 递增
		for len(deque) > 0 && prefixSum[i] <= prefixSum[deque[len(deque)-1]] {
			deque = deque[:len(deque)-1]
		}
		deque = append(deque, i)
	}
	if res <= len(A) {
		return res
	}
    return -1
}

````


