# [852. Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/)

## 题目

Let's call an array `arr` a **mountain** if the following properties hold:

- `arr.length >= 3`
- There exists some `i`with `0 < i < arr.length - 1`such that:
  - `arr[0] < arr[1] < ... arr[i-1] < arr[i]`
  - `arr[i] > arr[i+1] > ... > arr[arr.length - 1]`

Given an integer array `arr` that is **guaranteed** to be a mountain, return any `i` such that `arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`.

 

**Example 1:**

```
Input: arr = [0,1,0]
Output: 1
```

**Example 2:**

```
Input: arr = [0,2,1,0]
Output: 1
```

**Example 3:**

```
Input: arr = [0,10,5,2]
Output: 1
```

**Example 4:**

```
Input: arr = [3,4,5,1]
Output: 2
```

**Example 5:**

```
Input: arr = [24,69,100,99,79,78,67,36,26,19]
Output: 2
```

 

**Constraints:**

- `3 <= arr.length <= 104`
- `0 <= arr[i] <= 106`
- `arr` is **guaranteed** to be a mountain array.

 



**Follow up:** Finding the `O(n)` is straightforward, could you find an `O(log(n))` solution?

## 题目大意

我们把满足下列要求的数组 arr 称为山脉：

* arr.length >= 3
* 存在一些  `i`（`0 < i < arr.length - 1`）使得：
  * `arr[0] < arr[1] < ... arr[i-1] < arr[i]`
  * `arr[i] > arr[i+1] > ... > arr[arr.length - 1]`

给定一个确定是山脉的整型数组，返回任意一个满足arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]的 i .

## 解题思路

* 这道题目可以用“二分搜索”来做，不过需要注意的一点是缩小搜索区间的条件
  * arr[i - 1]  < arr[i] 左侧满足，右侧不满足
  * arr[i] > arr[i + 1] 右侧满足，左侧不满足
* 这道题目还可用三分法来解决，不过目前不是重点，以后再进行更深入的探讨
* 二分和三分
  * 二分通过用来解决单调区间找特定值的问题，
  * 三分通常用来解决单峰极值问题

````c++
class Solution {
public:
    // 解法一：Brute force
    /*
    int peakIndexInMountainArray(vector<int>& arr) {
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] > arr[i + 1]) {
                return i;
            }
        }
        
        return -1;
    }
    */
    
    // 解法二： 二分
    // FIXME 会发生数组下标越界
    /*
    int peakIndexInMountainArray(vector<int>& arr) {
        int lo = 0;
        int hi = arr.size() - 1;
        
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                return mid;
            }
            
            if (arr[mid] > arr[mid - 1] && arr[mid] < arr[mid + 1]) {
                lo = mid + 1;
            }
            
            if (arr[mid] < arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                hi = mid - 1;
            }
        }
        return -1;
    }
    */
    
    // 二分法：注意不同的条件结果不同
    /*
    int peakIndexInMountainArray(vector<int>& arr) {
        int lo = 0;
        int hi = arr.size() - 1;
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (arr[mid] > arr[mid + 1]) { // 右侧满足，左侧不满足
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;
    }*/
    
    int peakIndexInMountainArray(vector<int>& arr) {
        int lo = 0;
        int hi = arr.size() - 1;
        
        while (lo < hi) {
            int mid = (1L + lo + hi) / 2;
            
            if (arr[mid] > arr[mid - 1]) { // 左侧满足，右侧不满足
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        
        return lo;
    }
    
    // 三分法：
    int peakIndexInMountainArray(vector<int>& arr) {
        int lo = 0;
        int hi = arr.size() - 1;
        
        while (lo < hi) {
            int m1 = lo + (hi - lo) / 3;
            int m2 = hi - (hi - lo) / 3;
            
            if (arr[m1] > arr[m2]) {
                hi = m2 - 1;
            } else {
                lo = m1 + 1;
            }
        }
        return lo;   
    }
};
````

