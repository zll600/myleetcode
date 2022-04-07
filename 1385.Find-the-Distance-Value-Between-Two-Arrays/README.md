# [1385. Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)

Given two integer arrays `arr1` and `arr2`, and the integer `d`, *return the distance value between the two arrays*.

The distance value is defined as the number of elements `arr1[i]` such that there is not any element `arr2[j]` where `|arr1[i]-arr2[j]| <= d`.

 

**Example 1:**

```
Input: arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
Output: 2
Explanation: 
For arr1[0]=4 we have: 
|4-10|=6 > d=2 
|4-9|=5 > d=2 
|4-1|=3 > d=2 
|4-8|=4 > d=2 
For arr1[1]=5 we have: 
|5-10|=5 > d=2 
|5-9|=4 > d=2 
|5-1|=4 > d=2 
|5-8|=3 > d=2
For arr1[2]=8 we have:
|8-10|=2 <= d=2
|8-9|=1 <= d=2
|8-1|=7 > d=2
|8-8|=0 <= d=2
```

**Example 2:**

```
Input: arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
Output: 2
```

**Example 3:**

```
Input: arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
Output: 1
```

 

**Constraints:**

- `1 <= arr1.length, arr2.length <= 500`
- `-1000 <= arr1[i], arr2[j] <= 1000`
- `0 <= d <= 100`

## 题目大意

给你两个整数数组 `arr1` ， `arr2` 和一个整数 `d` ，请你返回两个数组之间的 *距离值* 。

`「距离值」` 定义为符合此距离要求的元素数目：对于元素 `arr1[i]` ，不存在任何元素 `arr2[j]` 满足 `|arr1[i]-arr2[j]| <= d` 

## 解题思路

### Solution 1:

这里直接使用嵌套循环就可以通过这道题目，因为这道题目的数据规模比较小

这种解法的时间复杂度是 (n^2)

````c++
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int res = 0;

        const int len1 = arr1.size();
        const int len2 = arr2.size();
        for (int i = 0; i < len1; ++i) {
            bool flag = false;
            for (int j = 0; j < len2; ++j) {
                if (abs(arr1[i] - arr2[j]) <= d) {
                    flag = true;
                }
            }
            if (!flag) {
                ++res;
            }
        }

        return res;
    }
};
````

### Solution 2: Binary Search

这里只是用这道题目练习一下二分查找，这里的数据规模其实也不需要做这一层优化

````c++
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        int res = 0;

        // 先将数据排序
        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());

        const int len1 = arr1.size();
        const int len2 = arr2.size();
        for (int i = 0; i < len1; ++i) {
            bool flag = false;

            // 二分查找，查找第一个大于 目标值的数
            int low = 0;
            int high = len2 - 1;
            while (low < high) {
                const int mid = low + (high - low) / 2;
                if (arr2[mid] < arr1[i]) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }

            // 将第一个大于的比较
            if (abs(arr1[i] - arr2[low]) <= d) {
                flag = true;
            }
            // 如果存在最后一个小于的数，也进行比较
            if (!flag && low - 1 >= 0 && abs(arr1[i] - arr2[low - 1]) <= d) {
                flag = true;
            }

            if (!flag) {
                ++res;
            }
        }

        return res;
    }
};
````
