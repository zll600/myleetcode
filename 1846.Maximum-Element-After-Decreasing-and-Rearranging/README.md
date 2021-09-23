# [1846. Maximum Element After Decreasing and Rearranging](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/)

You are given an array of positive integers `arr`. Perform some operations (possibly none) on `arr` so that it satisfies these conditions:

- The value of the **first** element in `arr` must be `1`.
- The absolute difference between any 2 adjacent elements must be **less than or equal to** `1`. In other words, `abs(arr[i] - arr[i - 1]) <= 1` for each `i` where `1 <= i < arr.length` (**0-indexed**). `abs(x)` is the absolute value of `x`.

There are 2 types of operations that you can perform any number of times:

- **Decrease** the value of any element of `arr` to a **smaller positive integer**.
- **Rearrange** the elements of `arr` to be in any order.

Return *the **maximum** possible value of an element in* `arr` *after performing the operations to satisfy the conditions*.

 

**Example 1:**

```
Input: arr = [2,2,1,2,1]
Output: 2
Explanation: 
We can satisfy the conditions by rearranging arr so it becomes [1,2,2,2,1].
The largest element in arr is 2.
```

**Example 2:**

```
Input: arr = [100,1,1000]
Output: 3
Explanation: 
One possible way to satisfy the conditions is by doing the following:
1. Rearrange arr so it becomes [1,100,1000].
2. Decrease the value of the second element to 2.
3. Decrease the value of the third element to 3.
Now arr = [1,2,3], which satisfies the conditions.
The largest element in arr is 3.
```

**Example 3:**

```
Input: arr = [1,2,3,4,5]
Output: 5
Explanation: The array already satisfies the conditions, and the largest element is 5.
```

 

**Constraints:**

- `1 <= arr.length <= 105`
- `1 <= arr[i] <= 109`

## 题目大意

给定一个整数数组 arr，进行一些操作使起满足下列条件：

- arr 中 第一个 元素必须为 1 。
- 任意相邻两个元素的差的绝对值 小于等于 1 ，也就是说，对于任意的 1 <= i < arr.length （数组下标从 0 开始），都满足 abs(arr[i] - arr[i - 1]) <= 1 。abs(x) 为 x 的绝对值。

你可以执行以下 2 种操作任意次：

- 减小 arr 中任意元素的值，使其变为一个 更小的正整数 。
- 重新排列 arr 中的元素，你可以以任意顺序重新排列。

返回经过一些操作满足上面的条件后 arr 中最大的值

## 解题思路

这道题目是一道贪心的题目，具体的思路就是排序后让第一个元素为 1，满足第一个条件，然后让这个数组非严格递增即可

具体的证明可以参考这篇题解：https://leetcode-cn.com/problems/maximum-element-after-decreasing-and-rearranging/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-yh9qt/

## 代码

`````c++
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        
        arr[0] = 1;
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] - arr[i - 1] > 1) {
                arr[i] = arr[i -1] + 1;
            }
        }
        
        return arr[arr.size() - 1];
    }
};
`````

