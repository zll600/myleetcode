# [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)

## 题目

Given an integer `n`, return *the number of structurally unique **BST'**s (binary search trees) which has exactly* `n` *nodes of unique values from* `1` *to* `n`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/18/uniquebstn3.jpg)

```
Input: n = 3
Output: 5
```

**Example 2:**

```
Input: n = 1
Output: 1
```

 

**Constraints:**

- `1 <= n <= 19`

## 题目大意

给定一个整数 n，求以 1 … n 为节点组成的二叉搜索树有多少种？

## 解题思路

#### Solution 1:

这道题目还是看题解吧，这里放上两篇题解：https://leetcode-cn.com/problems/unique-binary-search-trees/solution/hua-jie-suan-fa-96-bu-tong-de-er-cha-sou-suo-shu-b/，

https://books.halfrost.com/leetcode/ChapterFour/0001~0099/0096.Unique-Binary-Search-Trees/

````c++
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;
        
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        
        return dp[n];
    }
};
````

