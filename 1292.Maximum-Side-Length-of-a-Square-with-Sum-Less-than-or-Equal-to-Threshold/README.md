#### [1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold](https://leetcode.cn/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/)

Given a `m x n` matrix `mat` and an integer `threshold`, return *the maximum side-length of a square with a sum less than or equal to* `threshold` *or return* `0` *if there is no such square*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/12/05/e1.png)

```
Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
Output: 2
Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
```

**Example 2:**

```
Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]], threshold = 1
Output: 0
```

 

**Constraints:**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 300`
- `0 <= mat[i][j] <= 104`
- `0 <= threshold <= 105`



### 题目大意

给你一个大小为 `m x n` 的矩阵 `mat` 和一个整数阈值 `threshold`。

请你返回元素总和小于或等于 **阈值** 的正方形区域的最大边长；如果没有这样的正方形区域，则返回 `0`



## 解题思路





### Solution 1: Prefix Sum

这道题目可以参考这篇 [题解](https://leetcode.cn/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/solution/qing-xi-tu-jie-mo-neng-de-qian-zhui-he-by-hlxing/)



这里就是利用 二维前缀和来加速处理，然后在利用同样的思想来计算每个可能的正方形，最后得出结果

````c++
class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        const int m = mat.size();
        const int n = mat[0].size();
        
        // init prefix_sum
        vector<vector<int>> matrix_sum(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                matrix_sum[i][j] = mat[i - 1][j - 1] + matrix_sum[i - 1][j] + matrix_sum[i][j - 1]
                                    - matrix_sum[i - 1][j - 1];
            }
        }
        
        cout << m << " " << n << endl;
        // try to calculate every possible lengths
        int ans = 0;
        for (int len = 1; len <= min(m, n); ++len) {
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j) {
                    // index out of range 
                    if (i - len < 0 || j - len < 0) {
                        continue;
                    }
                    
                    int square = matrix_sum[i][j] - matrix_sum[i - len][j] - matrix_sum[i][j - len]
                                + matrix_sum[i - len][j - len];
                    if (square <= threshold) {
                        ans = max(ans, len);
                    }
                }
            }
        }
        return ans;
    }
};
````

