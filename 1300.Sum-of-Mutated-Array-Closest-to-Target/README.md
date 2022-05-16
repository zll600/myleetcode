# [1300. Sum of Mutated Array Closest to Target](https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/)

## 题目

Given an integer array `arr` and a target value `target`, return the integer `value` such that when we change all the integers larger than `value` in the given array to be equal to `value`, the sum of the array gets as close as possible (in absolute difference) to `target`.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from `arr`.

 

**Example 1:**

```
Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
```

**Example 2:**

```
Input: arr = [2,3,5], target = 10
Output: 5
```

**Example 3:**

```
Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361
```

 

**Constraints:**

- `1 <= arr.length <= 104`
- `1 <= arr[i], target <= 105`

## 题目大意

给你一个整数数组 `arr` 和一个目标值 `target` ，请你返回一个整数 `value` ，使得将数组中所有大于 `value` 的值变成 `value` 后，数组的和最接近  `target` （最接近表示两者之差的绝对值最小）。

如果有多种使得和最接近 `target` 的方案，请你返回这些整数中的最小值。请注意，答案不一定是 `arr` 中的数字

## 解题思路

通过看题目给出的例子，可以想到如果 数组元素之和 小于或者等于 target，那么 value 就是数组中的最大值，其余情况，需要从最大值开始向较小值的方向尝试，直到找到合适的位置（value 也可能不是数组中的值）

剩下的情况就只剩下 数组所有元素之和 大于  target 的情况了，这种情况，可以这样思考，将数组之和分摊到所有元素之上，也就是初始化 value = target // len(arr)，

这时一定满足 value * len(arr) < target, 然后在通过在在小范围改变 value 的值，使得总和总负方向最接近 target 即可，

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/sum-of-mutated-array-closest-to-target/solution/wu-xu-pai-xu-he-er-fen-you-hua-bao-li-fa-by-tinyli/)

### Solution 1: 

````Python3
class Solution:
    def findBestValue(self, arr: List[int], target: int) -> int:
        total = sum(arr)
        if total <= target:
            return max(arr)

        arr_len = len(arr)
        value = target // arr_len
        total, last = 0, 0

        while total < target:
            last = total
            total = 0

            for i in range(arr_len):
                total += arr[i] if value > arr[i] else value

            value += 1

        return value - 2 if abs(target - total) >= abs(target - last) else value - 1
````

### Solution 2: BinarySearch

这种解法对比 解法一，就是在求 value 的时候用二分来替换掉枚举，将 O(n) 降低为 log(n)

这里还要注意就是 python 的 除法和整除是不一样的

````Python3
class Solution:
    def findBestValue(self, arr: List[int], target: int) -> int:
        total = sum(arr)
        if total <= target:
            return max(arr)

        arr_len = len(arr)
        # 这里使用 二分来做
        # 做边界就是数组的均值，右边界就是 min(max(arr), target)
        left, right = target // arr_len, max(arr) if max(arr) <= target else target
        while left < right:
            mid = left + (right - left) // 2
            total = 0

            # 根据累加和来进行二分
            for i in range(arr_len):
                total += mid if arr[i] > mid else arr[i]

            if total < target:
                left = mid + 1
            else:
                right = mid - 1

        # 二分查找结束之后，这几个值都要尝试一下，找到最接近 target 中的最小的
        sum_mid, sum_left, sum_right = 0, 0, 0
        for i in range(arr_len):
            sum_mid += left if arr[i] > left else arr[i]
            sum_left += left - 1 if arr[i] > left - 1 else arr[i]
            sum_right += left + 1 if arr[i] > left + 1 else arr[i]

        # 这里的判断注意 等号
        if abs(target - sum_mid) <= abs(target - sum_right):
            return left if abs(target - sum_mid) < abs(target - sum_left) else left - 1

        return left + 1

````
