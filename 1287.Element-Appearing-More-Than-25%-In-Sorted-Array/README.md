# [1287. Element Appearing More Than 25% In Sorted Array](https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/)

Given an integer array **sorted** in non-decreasing order, there is exactly one integer in the array that occurs more than 25% of the time, return that integer.

 

**Example 1:**

```
Input: arr = [1,2,2,6,6,6,6,7,10]
Output: 6
```

**Example 2:**

```
Input: arr = [1,1]
Output: 1
```

 

**Constraints:**

- `1 <= arr.length <= 104`
- `0 <= arr[i] <= 105`

给定一个按照非降序排序的整数数组，返回出现次数超过 25% 次的数

## 解题思路


### Solution 1: 计数

这种解法利用了这里有序的特性，来累计频数，出现结果则直接返回

````c++
class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        const int len = arr.size();
        int target = (len + 1)/ 4;

        int cnt = 1;
        int cur = arr[0];
        for (int i = 1; i < len; ++i) {
            if (arr[i] == cur) {
                // 同一个数字
                ++cnt;
            } else {
                // 不同数字
                cur = arr[i];
                cnt = 1;
            }

            if (cnt > target) {
                break;
            }
        }

        return cur;
    }
};
````


