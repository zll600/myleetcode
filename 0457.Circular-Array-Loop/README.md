# [457. Circular Array Loop](https://leetcode.com/problems/circular-array-loop/)

## 题目

You are playing a game involving a **circular** array of non-zero integers `nums`. Each `nums[i]` denotes the number of indices forward/backward you must move if you are located at index `i`:

- If `nums[i]` is positive, move `nums[i]` steps **forward**, and
- If `nums[i]` is negative, move `nums[i]` steps **backward**.

Since the array is **circular**, you may assume that moving forward from the last element puts you on the first element, and moving backwards from the first element puts you on the last element.

A **cycle** in the array consists of a sequence of indices `seq` of length `k` where:

- Following the movement rules above results in the repeating index sequence `seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...`
- Every `nums[seq[j]]` is either **all positive** or **all negative**.
- `k > 1`

Return `true` *if there is a **cycle** in* `nums`*, or* `false` *otherwise*.

 

**Example 1:**

```
Input: nums = [2,-1,1,2,2]
Output: true
Explanation:
There is a cycle from index 0 -> 2 -> 3 -> 0 -> ...
The cycle's length is 3.
```

**Example 2:**

```
Input: nums = [-1,2]
Output: false
Explanation:
The sequence from index 1 -> 1 -> 1 -> ... is not a cycle because the sequence's length is 1.
By definition the sequence's length must be strictly greater than 1 to be a cycle.
```

**Example 3:**

```
Input: nums = [-2,1,-1,-2,-2]
Output: false
Explanation:
The sequence from index 1 -> 2 -> 1 -> ... is not a cycle because nums[1] is positive, but nums[2] is negative.
Every nums[seq[j]] must be either all positive or all negative.
```

 

**Constraints:**

- `1 <= nums.length <= 5000`
- `-1000 <= nums[i] <= 1000`
- `nums[i] != 0`

 

**Follow up:** Could you solve it in `O(n)` time complexity and `O(1)` extra space complexity?

## 题目大意

你正在玩一个涉及由非 0 数构造的环形数组的游戏，数组中的每一项 nums[i]代表如果你在 i 位置，你必须向前或者向后移动多少

* 如果 `nums[i]` 是正数，向前（下标递增方向）移动 `|nums[i]|` 步
* 如果 `nums[i]` 是负数，向后（下标递减方向）移动 `|nums[i]|` 步

因为数组是 **环形** 的，所以可以假设从最后一个元素向前移动一步会到达第一个元素，而第一个元素向后移动一步会到达最后一个元素。

数组中的 **循环** 由长度为 `k` 的下标序列 `seq` 标识：

* 遵循上述移动规则将导致一组重复下标序列 seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
* 所有 nums[seq[j]] 应当不是 全正 就是 全负
* k > 1

如果数组中存在循环就返回 true，否则返回 false

进阶要求：你能设计一个时间复杂度为 `O(n)` 且额外空间复杂度为 `O(1)` 的算法吗？

## 解题思路

题干有点长，概括一点就是给出一个循环数组，数组的值代表向前或者向后移动的距离，问数组中是否存在一个循环，这个循环的长度大于 1，且必须是同一方向上的。

### 解法1（双指针）

这道题目前C++写不出来，所以先写一个Go 的版本，具体可以参考这篇题解：https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0457.Circular-Array-Loop/

基本思想是利用循环链表的思想，利用快慢指针来找环，不过这里需要注意的是环中至少需要有一个元素，另一个是循环的方向必然是同向的，这个可以利用 相乘后结果为正计算，另外对于遍历过的元素置0，作标记

````c++
func circularArrayLoop(nums []int) bool {
	if len(nums) == 0 {
		return false
	}
	for i := 0; i < len(nums); i++ {
		if nums[i] == 0 {
			continue
		}
		// slow/fast pointer
		slow, fast, val := i, getNextIndex(nums, i), 0
		for nums[fast]*nums[i] > 0 && nums[getNextIndex(nums, fast)]*nums[i] > 0 {
			if slow == fast {
				// check for loop with only one element
				if slow == getNextIndex(nums, slow) {
					break
				}
				return true
			}
			slow = getNextIndex(nums, slow)
			fast = getNextIndex(nums, getNextIndex(nums, fast))
		}
		// loop not found, set all element along the way to 0
		slow, val = i, nums[i]
		for nums[slow]*val > 0 {
			next := getNextIndex(nums, slow)
			nums[slow] = 0
			slow = next
		}
	}
	return false
}

func getNextIndex(nums []int, index int) int {
	return ((nums[index]+index)%len(nums) + len(nums)) % len(nums)
}
````

