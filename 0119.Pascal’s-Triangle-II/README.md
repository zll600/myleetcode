# [119. Pascal’s Triangle II](https://leetcode.com/problems/pascals-triangle-ii/)

## 题目

Given an integer `rowIndex`, return the `rowIndexth` (**0-indexed**) row of the **Pascal's triangle**.

In **Pascal's triangle**, each number is the sum of the two numbers directly above it as shown:

![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

 

**Example 1:**

```
Input: rowIndex = 3
Output: [1,3,3,1]
```

**Example 2:**

```
Input: rowIndex = 0
Output: [1]
```

**Example 3:**

```
Input: rowIndex = 1
Output: [1,1]
```

 

**Constraints:**

- `0 <= rowIndex <= 33`

 

**Follow up:** Could you optimize your algorithm to use only `O(rowIndex)` extra space?

## 题目大意

给定一个行索引，返回杨辉三角的该行

## 解题思路

* 这道题目可以看作一道 DP 题，其中递推公式已经给出
* 二维 dp不满要求，必须进行一维优化

## 代码

````c++
class Solution {
public:
    
    vector<int> getRow(int rowIndex) {
        vector<int> dp(rowIndex + 1);
        dp[0] = 1;
        
        for (int i = 1; i <= rowIndex; ++i) {
            for (int j = i; j >= 0; --j) {
                if (j == 0) {
                    dp[j] = 1;
                } else {
                    dp[j] += dp[j - 1];
                }
            }
        }
        
        return dp;
    }
};
````

