# [1090. Largest Values From Labels](https://leetcode.cn/problems/largest-values-from-labels/)

## 题目

There is a set of `n` items. You are given two integer arrays `values` and `labels` where the value and the label of the `ith` element are `values[i]` and `labels[i]` respectively. You are also given two integers `numWanted` and `useLimit`.

Choose a subset `s` of the `n` elements such that:

- The size of the subset `s` is **less than or equal to** `numWanted`.
- There are **at most** `useLimit` items with the same label in `s`.

The **score** of a subset is the sum of the values in the subset.

Return *the maximum **score** of a subset* `s`.

 

**Example 1:**

```
Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1
Output: 9
Explanation: The subset chosen is the first, third, and fifth items.
```

**Example 2:**

```
Input: values = [5,4,3,2,1], labels = [1,3,3,3,2], numWanted = 3, useLimit = 2
Output: 12
Explanation: The subset chosen is the first, second, and third items.
```

**Example 3:**

```
Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], numWanted = 3, useLimit = 1
Output: 16
Explanation: The subset chosen is the first and fourth items.
```

 

**Constraints:**

- `n == values.length == labels.length`
- `1 <= n <= 2 * 104`
- `0 <= values[i], labels[i] <= 2 * 104`
- `1 <= numWanted, useLimit <= n`

## 题目大意

我们有一个 `n` 项的集合。给出两个整数数组 `values` 和 `labels` ，第 `i` 个元素的值和标签分别是 `values[i]` 和 `labels[i]`。还会给出两个整数 `numWanted` 和 `useLimit`

从 n 个元素中选择一个子集 `s` :

-   子集 `s` 的大小 小于或等于 `numWanted`
-   `s` 中 最多 有相同标签的 `useLimit` 项

一个子集的 分数 是该子集的值之和

返回子集 `s` 的最大 分数

## 解题思路

### Solution 1:

这里利用 multimap 的有序性，直接遍历，选取最大值即可，在选取的时候注意每个 label 的数的限制即可

````c++
class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        const int n = values.size();
        // multimap is sorted
        multimap<int, int> records;
        for (int i = 0; i < n; ++i) {
            records.emplace(values[i], labels[i]);
        }

        auto iter = records.crbegin();
        unordered_map<int, int> label_freq;
        int res = iter->first;
        // cout << res << " -- ";
        ++label_freq[iter->second];
        ++iter;
        int cnt = 1;
        while (cnt < numWanted && iter != records.crend()) {
            ++label_freq[iter->second];
            // cout << iter->first << " -- ";
            if (label_freq[iter->second] <= useLimit) {
                // cout << iter->first << " -- ";
                res += iter->first;
                ++cnt;
            }
            ++iter;
        }
        return res;
    }
};
````
