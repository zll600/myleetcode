#### [1267. Count Servers that Communicate](https://leetcode.cn/problems/count-servers-that-communicate/)

You are given a map of a server center, represented as a `m * n` integer matrix `grid`, where 1 means that on that cell there is a server and 0 means that it  is no server. Two servers are said to communicate if they are on the  same row or on the same column.
 
 Return the number of servers that communicate with any other server.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/11/14/untitled-diagram-6.jpg)

```
Input: grid = [[1,0],[0,1]]
Output: 0
Explanation: No servers can communicate with others.
```

**Example 2:**

**![img](https://assets.leetcode.com/uploads/2019/11/13/untitled-diagram-4.jpg)**

```
Input: grid = [[1,0],[1,1]]
Output: 3
Explanation: All three servers can communicate with at least one other server.
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/11/14/untitled-diagram-1-3.jpg)

```
Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
Output: 4
Explanation: The two servers in the first row can communicate with each other. The two servers in the third column can communicate with each other. The server at right bottom corner can't communicate with any other server.
```

 

**Constraints:**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m <= 250`
- `1 <= n <= 250`
- `grid[i][j] == 0 or 1`



### 解题思路

这道题目拿到肯定首先想到的是并查集，将二维数组展开至一维，然后对在同一行或者同一列的 server 合并即可

### Solution 1:

这道题题目也可以简单模拟一下，不使用并查集这种办法

- 首先统计出么一行和每一列的 server 的数目
- 找出不符合条件的位置的数目：
  - 该位置没有 server
  - 改为的server 不能和其他 server 进行交流

````c++
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        
        // 统计每一行和每一列的 server 的总数
        vector<int> rows(m), cols(n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    ++rows[i];
                    ++cols[j];
                }
            }
        }
        
        // 逆向思维
        // 找到没有 server 的位置数目或者无法和其他 server 交流的位置的数目
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1
                   && rows[i] < 2
                    && cols[j] < 2) {
                    ++res;
                } else if (grid[i][j] == 0) {
                    ++res;
                }
            }
        }
        return m * n - res;
    }
};

````

