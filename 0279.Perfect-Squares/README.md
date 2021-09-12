# [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/)

## 题目

Given an integer `n`, return *the least number of perfect square numbers that sum to* `n`.

A **perfect square** is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, `1`, `4`, `9`, and `16` are perfect squares while `3` and `11` are not.

 

**Example 1:**

```
Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
```

**Example 2:**

```
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
```

 

**Constraints:**

- `1 <= n <= 104`

## 题目大意

给定一个整数，返回需要多少个完全平方数相加等于 n，

## 解题思路

* 可以把这道题抽象为求在一棵以 n 为根节点的 N 叉树中，找到路径之和等于 n 的最短路径，可以使用 BFS，
* 这道题目也可以作为一道 DP 完全背包来求解，
  * 给定来若干数字，每个数字可以用无限次，求凑出目标值使用的数字的最小数目，

## 代码

````c++
class Solution {
public:
    /*
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i * i <= n; ++i) {
            for (int j = i * i; j <= n; ++j) {
                if (dp[j - i * i] != INT_MAX) {
                    dp[j] = min(dp[j], dp[j - i * i] + 1);
                }
            }
        }
        if (dp[n] == INT_MAX) {
            return -1;
        }
        
        return dp[n];
    }*/
    
    int numSquares(int n) {        
        queue<int> que;
        unordered_set<int> visit;
        que.push(n);
        int level = 0;
        visit.insert(n);
        
        while (!que.empty()) {
            int len = que.size();   // 下一层要遍历的节点的数目，
            ++level;
            
            for (int i = 0; i < len; ++i) {
                int cur = que.front();
                que.pop();
                // cout << cur << "---";
                
                for (int j = 1; j * j <= cur; ++j) {
                    int tmp = cur - j * j;
                    if (tmp == 0) {
                        return level;
                    }
                    
                    if (visit.find(tmp) == visit.end()) {   // 注意这里判断的是 tmp 不是 j * j，我们减掉的是完全平方数
                        que.push(tmp);
                        visit.insert(tmp);
                    }
                }
            }
            // cout << endl;
        }
        
        return level;
    }
};
````

