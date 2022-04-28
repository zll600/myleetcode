# [969. Pancake Sorting](https://leetcode.com/problems/pancake-sorting/)

## 题目

Given an array of integers `arr`, sort the array by performing a series of **pancake flips**.

In one pancake flip we do the following steps:

- Choose an integer `k` where `1 <= k <= arr.length`.
- Reverse the sub-array `arr[0...k-1]` (**0-indexed**).

For example, if `arr = [3,2,1,4]` and we performed a pancake flip choosing `k = 3`, we reverse the sub-array `[3,2,1]`, so `arr = [1,2,3,4]` after the pancake flip at `k = 3`.

Return *an array of the* `k`*-values corresponding to a sequence of pancake flips that sort* `arr`. Any valid answer that sorts the array within `10 * arr.length` flips will be judged as correct.

 

**Example 1:**

```
Input: arr = [3,2,4,1]
Output: [4,2,4,3]
Explanation: 
We perform 4 pancake flips, with k values 4, 2, 4, and 3.
Starting state: arr = [3, 2, 4, 1]
After 1st flip (k = 4): arr = [1, 4, 2, 3]
After 2nd flip (k = 2): arr = [4, 1, 2, 3]
After 3rd flip (k = 4): arr = [3, 2, 1, 4]
After 4th flip (k = 3): arr = [1, 2, 3, 4], which is sorted.
```

**Example 2:**

```
Input: arr = [1,2,3]
Output: []
Explanation: The input is already sorted, so there is no need to flip anything.
Note that other answers, such as [3, 3], would also be accepted.
```

 

**Constraints:**

- `1 <= arr.length <= 100`
- `1 <= arr[i] <= arr.length`
- All integers in `arr` are unique (i.e. `arr` is a permutation of the integers from `1` to `arr.length`).

## 题目大意

给定一个数组 `arr`，要求输出“煎饼排序”的步骤，使得最终数组是从小到大有序的。

“煎饼排序”步骤如下，

- 每次排序都反转前 n 个数，n 小于数组的长度。

**限制**：

- 数组中数的范围是 [1, arr.length - 1]

## 解题思路



### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode.com/problems/pancake-sorting/)

这里的思路就是，我们没一轮都让最大的数回到合适的位置上即可，那么这里有两步操作

- 将 到最大值为止的所有数进行一次排序
- 将 此轮得到的最大值放到合适的位置

````c++
class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        // 如果已经有序，直接返回即可
        if (is_sorted(arr.begin(), arr.end())) {
            return {};
        }

        vector<int> res;
        int len = arr.size();
        while (len > 0) {
            // 找到最大的值就是数组的长度
            auto it = find(arr.begin(), arr.end(), len);
            // 计算出下标
            int idx = it - arr.begin();

            // 如果这个最大值，不再合理的位置上，就必须进行排序
            if (idx != len - 1) {
                // 这里是为了让 最大值放在第一位上
                Reverse(arr, idx);
                // 这里是为了让最大值放在该放的位置上
                Reverse(arr, len - 1);
                // 将两次结果都加入到结果集中
                res.push_back(idx + 1);
                res.push_back(len);
            }
            --len;
        }

        return res;
    }

 private:
    // 进行 排序
    void Reverse(vector<int>& arr, int k) {
        int i = 0;
        while (i < k) {
            swap(arr[i], arr[k]);
            ++i;
            --k;
        }
    }
};
````
