# [1131. Maximum of Absolute Value Expression](https://leetcode.cn/problems/maximum-of-absolute-value-expression/)

## 题目

Given two arrays of integers with equal lengths, return the maximum value of:

```
|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
```

where the maximum is taken over all `0 <= i, j < arr1.length`.

 

**Example 1:**

```
Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
Output: 13
```

**Example 2:**

```
Input: arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
Output: 20
```

 

**Constraints:**

- `2 <= arr1.length == arr2.length <= 40000`
- `-10^6 <= arr1[i], arr2[i] <= 10^6`

## 解题思路

给你两个长度相等的整数数组，返回下面表达式的最大值：

`|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|`

其中下标 `i`，`j` 满足 `0 <= i, j < arr1.length`

## 解题思路

### Solution 1: Bruce force(TLE)

暴力枚举所有的可能，最终会超时

````c++
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        const int len = arr1.size();

        int res = 0;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                res = max(res, abs(arr1[i] - arr1[j]) + abs(arr2[i] - arr2[j]) + abs(i - j));
            }
        }
        return res;
    }
};
````

### Solution 2: Math

这种解法可以参考 [这篇题解](https://leetcode.cn/problems/maximum-of-absolute-value-expression/solution/python-jie-fa-bao-li-shu-xue-by-jiayangwu/)

这种解法使用数学变形，去掉绝对值符号，分类讨论

````c++
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        const int len = arr1.size();
        
        int A = INT_MIN, B = INT_MIN, C = INT_MIN, D = INT_MIN;
        int a = INT_MAX, b = INT_MAX, c = INT_MAX, d = INT_MAX;
        for (int i = 0; i < len; ++i) {
            int x = arr1[i], y = arr2[i];
            
            A = max(A, x + y + i);
            a = min(a, x + y + i);
            B = max(B, x + y - i);
            b = min(b, x + y - i);
            C = max(C, x - y + i);
            c = min(c, x - y + i);
            D = max(D, x - y - i);
            d = min(d, x - y - i);
        }
        
        return max(A - a, max(B - b, max(C - c, D - d)));
    }
};
````
