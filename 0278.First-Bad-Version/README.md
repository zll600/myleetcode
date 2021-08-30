# [278. First Bad Version](https://leetcode.com/problems/first-bad-version/)

## 题目

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have `n` versions `[1, 2, ..., n]` and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API `bool isBadVersion(version)` which returns whether `version` is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

 

**Example 1:**

```
Input: n = 5, bad = 4
Output: 4
Explanation:
call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true
Then 4 is the first bad version.
```

**Example 2:**

```
Input: n = 1, bad = 1
Output: 1
```

 

**Constraints:**

- `1 <= bad <= n <= 231 - 1`

## 题目大意

你是一名产品经理，最近你领导的团队开发出了一项新产品。不幸的是，最新的版本出现了质量问题，因为每个版本都是基于之前的版本开发的，所以在一个错误的俄版本之后都是错误的版本，

假设你有 n 个版本号 [1, 2, ..., n] 你想要找出第一个引起其他错误的错误的版本，

你可以通过调用一个 API isBadVersion(version)来判断这个版本是否是错误的，实现一个甘薯找到第一个错误的版本，你应该减少掉调用API 的次数。

## 解题思路

* 可以利用二分搜索来找到第一个错误的版本，这道题目和第 374 题都属于二分查找答案的题目

## 代码

`````c++
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    // 解法一：
    /*
    int firstBadVersion(int n) {
        int lo = 1;
        int hi = n;
        
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (isBadVersion(mid)) {    // target <= nums[mid] 找到第一个大于等于给定条件的
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;	// 第一个是糟糕的
    }
    */
    
    // 解法二：
    int firstBadVersion(int n) {
        int lo = 1;
        int hi = n;
        
        while (lo < hi) {
            int mid = (1L + lo + hi) / 2L;   // 这里存在溢出问题，这里 1L 必须放在lo + hi 之前或者中间
                                             // 才能起到提升整型的作用
            if (!isBadVersion(mid)) {		// 找到最后一个不满条件的
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        
        return !isBadVersion(hi) ? hi + 1 : hi;	// 最后一个不是糟糕的，
    }
    
};
`````

