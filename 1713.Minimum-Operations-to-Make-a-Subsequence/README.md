# [1713. Minimum Operations to Make a Subsequence](https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/)

## 题目

You are given an array `target` that consists of **distinct** integers and another integer array `arr` that **can** have duplicates.

In one operation, you can insert any integer at any position in `arr`. For example, if `arr = [1,4,1,2]`, you can add `3` in the middle and make it `[1,4,3,1,2]`. Note that you can insert the integer at the very beginning or end of the array.

Return *the **minimum** number of operations needed to make* `target` *a **subsequence** of* `arr`*.*

A **subsequence** of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, `[2,7,4]` is a subsequence of `[4,2,3,7,2,1,4]` (the underlined elements), while `[2,4,2]` is not.

 

**Example 1:**

```
Input: target = [5,1,3], arr = [9,4,2,3,4]
Output: 2
Explanation: You can add 5 and 1 in such a way that makes arr = [5,9,4,1,2,3,4], then target will be a subsequence of arr.
```

**Example 2:**

```
Input: target = [6,4,8,1,3,2], arr = [4,7,6,2,3,8,6,1]
Output: 3
```

 

**Constraints:**

- `1 <= target.length, arr.length <= 105`
- `1 <= target[i], arr[i] <= 109`
- `target` contains no duplicates.

## 题目大意

给定一个数组由不同的证书组成的数组 target ，和含有重复的数字组成的数组 arr，

每一次操作中，你可以在 arr 的任意位置插入任一整数。比方说，如果 arr = [1,4,1,2] ，那么你可以在中间添加 3 得到 [1,4,3,1,2] 。你可以在数组最开始或最后面添加整数。

返回让 target 成为 arr 子序列的最少操作数，

## 解题思路

分析题目之后，我们可以发现这是一道求最长公共子序列的题目，只要求得 target 中的字符，有多少个没有出现在 arr 中即可，所以这道题目是可以利用 DP 来求解的，这里放上一篇题解，这个题还需要好好消化消化：

https://leetcode-cn.com/problems/minimum-operations-to-make-a-subsequence/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-oj7yu/

## 代码

`````c++
class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        int n = target.size();
        unordered_map<int, int> pos;
        for (int i = 0; i < n; ++i) {
            pos[target[i]] = i;
        }
        
        vector<int> a;
        for (int val : arr) {
            if (pos.find(val) != pos.end()) {
                int idx = pos[val];
                auto it = lower_bound(a.begin(), a.end(), idx);
                if (it != a.end()) {
                    *it = idx;
                } else {
                    a.push_back(idx);
                }
            }
        }
        
        return n - a.size();
    }
};
`````



