# [1306. Jump Game III](https://leetcode.com/problems/jump-game-iii/)

## 题目

Given an array of non-negative integers `arr`, you are initially positioned at `start` index of the array. When you are at index `i`, you can jump to `i + arr[i]` or `i - arr[i]`, check if you can reach to **any** index with value 0.

Notice that you can not jump outside of the array at any time.

 

**Example 1:**

```
Input: arr = [4,2,3,0,3,1,2], start = 5
Output: true
Explanation: 
All possible ways to reach at index 3 with value 0 are: 
index 5 -> index 4 -> index 1 -> index 3 
index 5 -> index 6 -> index 4 -> index 1 -> index 3 
```

**Example 2:**

```
Input: arr = [4,2,3,0,3,1,2], start = 0
Output: true 
Explanation: 
One possible way to reach at index 3 with value 0 is: 
index 0 -> index 4 -> index 1 -> index 3
```

**Example 3:**

```
Input: arr = [3,0,2,1,2], start = 2
Output: false
Explanation: There is no way to reach at index 1 with value 0.
```

 

**Constraints:**

- `1 <= arr.length <= 5 * 104`
- `0 <= arr[i] < arr.length`
- `0 <= start < arr.length`

## 题目大意

这里有一个非负整数数组 arr，你最开始位于该数组的起始下标 start 处。当你位于下标 i 处时，你可以跳到 i + arr[i] 或者 i - arr[i]。请你判断自己是否能够跳到对应元素值为 0 的 任一 下标处。注意，不管是什么情况下，你都无法跳到数组之外

## 解题思路

这道题目很容易想到递归，递归到每一个位置 i

- 如果 arr[i] 为 0，则直接返回 true
- 如果不为 0，递归遍历 i + arr[i] 和 i + arr[i] 的位置，
- 如果下标越界返回 false

但是即使对上述情况都做一个处理，还是有能无法是递归正常终止，所以 这里还需要记录每个位置有没有访问过

如果对这里对访问过的位置最标记是否会影响结果有疑问，可以这样想，

- 如果一个位置可以到达结果，那么从这个位置除法的任意一条线路都可以到达，不用第二次访问也可以的，也可以使用题目中给的例子
- 如果一个位置不可以到达结果，那么经过这个位置的任意一条路线都无法到达最终的结果

### Solution 1: DFS

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1300~1399/1306.Jump-Game-III/)

这里采用染色的方法来做标记，直接修改原数组

````c++
func canReach(arr []int, start int) bool {
    if start >= 0 && start < len(arr) && arr[start] < len(arr) {
        jump := arr[start]
        arr[start] += len(arr)
        return jump == 0 || canReach(arr, start + jump) || canReach(arr, start - jump)
    }
    return false
}
````
