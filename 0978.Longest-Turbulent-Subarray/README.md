# [978. Longest Turbulent Subarray](https://leetcode.com/problems/longest-turbulent-subarray/)

## 题目

Given an integer array `arr`, return *the length of a maximum size turbulent subarray of* `arr`.

A subarray is **turbulent** if the comparison sign flips between each adjacent pair of elements in the subarray.

More formally, a subarray `[arr[i], arr[i + 1], ..., arr[j]]` of `arr` is said to be turbulent if and only if:

- For

   

  ```
  i <= k < j
  ```

  :

  - `arr[k] > arr[k + 1]` when `k` is odd, and
  - `arr[k] < arr[k + 1]` when `k` is even.

- Or, for

   

  ```
  i <= k < j
  ```

  :

  - `arr[k] > arr[k + 1]` when `k` is even, and
  - `arr[k] < arr[k + 1]` when `k` is odd.

 

**Example 1:**

```
Input: arr = [9,4,2,10,7,8,8,1,9]
Output: 5
Explanation: arr[1] > arr[2] < arr[3] > arr[4] < arr[5]
```

**Example 2:**

```
Input: arr = [4,8,12,16]
Output: 2
```

**Example 3:**

```
Input: arr = [100]
Output: 1
```

 

**Constraints:**

- `1 <= arr.length <= 4 * 104`
- `0 <= arr[i] <= 109`

## 题目大意

给定一个数组，求出最长的摆动数组，摆动数组就是比较符号在相邻两个元素之间翻转

## 解题思路

* 利用“滑动窗口”，用一个变量记录下一次两个数比较需要的出的结果，
  * 若满足，则扩大窗口，
  * 若不满足，则收缩窗口，每次收缩窗口时，判断，
    * 如果不是因为出现连续的元素，则更新结果，
    * 如果是因为出现连续的元素而导致窗口收缩，则不更新结果
  * 若出现连续多个元素相等的情况，则最终窗口会缩小为1，左右边界交替前进，至最终跳过这段
* 利用“模拟”，用两个变量分别记录上升和下降的序列的长度，一旦元素相等了，就同时置为1，其他时候按照上升和下降来更新这两个变量，最终选出二者中最大的

## 代码

````go
// 解法一 模拟法
func maxTurbulenceSize(A []int) int {
	inc, dec := 1, 1
	maxLen := min(1, len(A))
	for i := 1; i < len(A); i++ {
		if A[i-1] < A[i] {
			inc = dec + 1
			dec = 1
		} else if A[i-1] > A[i] {
			dec = inc + 1
			inc = 1
		} else {
			inc = 1
			dec = 1
		}
		maxLen = max(maxLen, max(inc, dec))
	}
	return maxLen
}

// 解法二 滑动窗口
func maxTurbulenceSize1(A []int) int {
	if len(A) == 1 {
		return 1
	}
	// flag > 0 代表下一个数要大于前一个数，flag < 0 代表下一个数要小于前一个数
	res, left, right, flag, lastNum := 0, 0, 0, A[1]-A[0], A[0]
	for left < len(A) {
		if right < len(A)-1 && ((A[right+1] > lastNum && flag > 0) || (A[right+1] < lastNum && flag < 0) || (right == left)) {
			right++
			flag = lastNum - A[right]
			lastNum = A[right]
		} else {
			if flag != 0 {
				res = max(res, right-left+1)
			}
			left++
		}
	}
	return max(res, 1)
}
````

