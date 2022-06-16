# [1200. Minimum Absolute Difference](https://leetcode.com/problems/minimum-absolute-difference/)

## 题目

Given an array of **distinct** integers `arr`, find all pairs of elements with the minimum absolute difference of any two elements.

Return a list of pairs in ascending order(with respect to pairs), each pair `[a, b]` follows

- `a, b` are from `arr`
- `a < b`
- `b - a` equals to the minimum absolute difference of any two elements in `arr`

 

**Example 1:**

```
Input: arr = [4,2,1,3]
Output: [[1,2],[2,3],[3,4]]
Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
```

**Example 2:**

```
Input: arr = [1,3,6,10,15]
Output: [[1,3]]
```

**Example 3:**

```
Input: arr = [3,8,-10,23,19,-4,-14,27]
Output: [[-14,-10],[19,23],[23,27]]
```

 

**Constraints:**

- `2 <= arr.length <= 105`
- `-106 <= arr[i] <= 106`

## 题目大意

给你个整数数组 `arr`，其中每个元素都 *不相同*。

请你找到所有具有最小绝对差的元素对，并且按升序的顺序返回。

## 解题思路

这道题目需要解决的问题有：

- 求出arr 中的最小差值
- 找出具有最小差值的元素对
- 这些元素对需要按照升序的顺序返回

### Solution 1:

这道题目比较简单，通过排序可以就可以很容易的求出答案

````c++
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        int min_diff = INT_MAX;
        sort(arr.begin(), arr.end());

        const int len = arr.size();
        for (int i = 1; i < len; ++i) {
            int diff = arr[i] - arr[i - 1];
            min_diff = min(diff, min_diff);
        }

        vector<vector<int>> res;
        for (int i = 1; i < len; ++i) {
            if (arr[i] - arr[i - 1] == min_diff) {
                res.push_back(vector<int>{arr[i - 1], arr[i]});
            }
        }

        return res;
    }
};
````
