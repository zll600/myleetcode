# [1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold](https://leetcode-cn.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/)

## 题目

Given an array of integers `arr` and two integers `k` and `threshold`.

Return *the number of sub-arrays* of size `k` and average greater than or equal to `threshold`.

 

**Example 1:**

```
Input: arr = [2,2,2,2,5,5,5,8], k = 3, threshold = 4
Output: 3
Explanation: Sub-arrays [2,5,5],[5,5,5] and [5,5,8] have averages 4, 5 and 6 respectively. All other sub-arrays of size 3 have averages less than 4 (the threshold).
```

**Example 2:**

```
Input: arr = [1,1,1,1,1], k = 1, threshold = 0
Output: 5
```

**Example 3:**

```
Input: arr = [11,13,17,23,29,31,7,5,2,3], k = 3, threshold = 5
Output: 6
Explanation: The first 6 sub-arrays of size 3 have averages greater than 5. Note that averages are not integers.
```

**Example 4:**

```
Input: arr = [7,7,7,7,7,7,7], k = 7, threshold = 7
Output: 1
```

**Example 5:**

```
Input: arr = [4,4,4,4], k = 4, threshold = 1
Output: 1
```

 

**Constraints:**

- `1 <= arr.length <= 10^5`
- `1 <= arr[i] <= 10^4`
- `1 <= k <= arr.length`
- `0 <= threshold <= 10^4`

## 题目大意

给定一个整数数组 arr 和两个整数 k 和 threshold

请你返回长度为 `k` 且平均值大于等于 `threshold` 的子数组数目。

## 解题思路

### Solution 1:

这道题目与连续子数组有关，而且是求和，所以可以考虑使用滑动窗口

这个解法的步骤比较清晰

`````c++
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        long target = k * threshold;
        long sum = 0;

        int ans = 0;
        const int size = arr.size();
        for (int i = 0; i < k; ++i) {  // 先将窗口扩展至 k 个元素，
            sum += arr[i];
        }
        if (sum >= target) {  // 检查是否符合条件
            ++ans;
        }

        for (int i = k; i < size; ++i) {
            sum -= arr[i - k];  // 右移左边界
            sum += arr[i];  // 右移右边界
            if (sum >= target) {
                ++ans;
            }
        }

        return ans;
    }
};
`````

### Solution 2:

这是花花酱的解法

``````c++
class Solution {
public:
  int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int ans = 0;
        int sum = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum += arr[i];
            if (i + 1 >= k) {  // 这里注意i 从 0 开始，如果 i >= k，说明窗口中多了一个元素
                if (threshold * k <= sum) {
                    ++ans;
                }
                sum -= arr[i + 1 - k];
            }
        }

        return ans;
    }
};
``````



### Solution: Python3



````python3
class Solution:
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        ans = 0
        total = 0
        
        for i in range(len(arr)):
            total += arr[i]
            
            if i - k + 1 >= 0:
                if total >= threshold * k:
                    ans += 1
                
                total -= arr[i - k + 1]
        return ans
````

