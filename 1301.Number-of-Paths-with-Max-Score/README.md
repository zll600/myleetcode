# [1301. Number of Paths with Max Score](https://leetcode.com/problems/number-of-paths-with-max-score/)

## 题目

You are given a square `board` of characters. You can move on the board starting at the bottom right square marked with the character `'S'`.

You need to reach the top left square marked with the character `'E'`. The rest of the squares are labeled either with a numeric character `1, 2, ..., 9` or with an obstacle `'X'`. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, **taken modulo `10^9 + 7`**.

In case there is no path, return `[0, 0]`.

 

**Example 1:**

```
Input: board = ["E23","2X2","12S"]
Output: [7,1]
```

**Example 2:**

```
Input: board = ["E12","1X1","21S"]
Output: [4,2]
```

**Example 3:**

```
Input: board = ["E11","XXX","11S"]
Output: [0,0]
```

 

**Constraints:**

- `2 <= board.length == board[i].length <= 100`

## 题目大意

给定一个字符窗正方形，你可以从正方形右下角 ‘S’处开始移动，你的目标是到达左上角的‘E’，数组的剩余部分是数组1，2，3....,或者是障碍的‘X’，在每一次移动中，你可以向左，向上，或者左是左上方，返回一个列表，第一个收集的最大总分数、第二个是收集最大分数的方案数，

如果没有任何路径返回[0, 0];

## 解题思路

* 这道题其实是两个路径 DP，求得最大分数，求得最大得分的方案数
* 求最大分数：
  * 状态定义 ：`dp[x][y]`表示到达位置(x, y)，的最大分数
  * 初始化：用 INT_MIN 标记无法访问的位置
  * 状态转移：`dp[x][y] = max(dp[x - 1][y], dp[x][y + 1], dp[x + 1][y + 1]) + board[x][y]`
* 求得的最大方案数：
  * 状态定义：`dp[x][y]` 表示到达位置(x, y)，得到最大分数的方案数
  * 初始化：
  * 状态转移：这里需要注意，最大值不一定使由一个位置得出，具体看代码，这里大概的做法是：如果转之后的结果和

## 代码

`````c++
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        n = board.size();
        vector<vector<char>> matrix;
        ToMatrix(board, matrix);

        // 求得最大的分数
        vector<int> sum(n * n, 0);
        // 求路径数
        vector<int> path(n * n, 0);

        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int idx = GetIdx(i, j);


                // 初始化
                // path[idx] = 1，到达起点的只有一条路径
                // sum[idx] = 0，起点的整数之和为
                if (i == n - 1 && j == n - 1) {
                    path[idx] = 1;
                    continue;
                }

                // 遇到障碍点
                // sum[idx] = INT_MIN，障碍点不可访问，得分为无效值，
                // path[idx] = 0，障碍点不可访问，路径数为 0，
                if (matrix[i][j] == 'X') {
                    sum[idx] = INT_MIN;
                    continue;
                }

                // 如果是第一个格子，得分为0，否则计算得分
                int val = (i == 0 && j == 0) ? 0 : matrix[i][j] - '0';

                // 当前位置的最大得分，和到达当前位置的路径数
                int score = INT_MIN;    // 无效值
                int route = 0;
                
                // 如果下面合法，向下转移
                if (i + 1 < n) {
                    int cur = sum[GetIdx(i + 1, j)] + val;
                    int cnt = path[GetIdx(i + 1, j)];
                    update(cur, cnt, &score, &route);
                }
                
                // 如果右面合法，向左转移
                if (j + 1 < n) {
                    int cur = sum[GetIdx(i, j + 1)] + val;
                    int cnt = path[GetIdx(i, j + 1)];
                    update(cur, cnt, &score, &route);
                }
                
                // 如果右下合法，向右下转移
                if (i + 1 < n && j + 1 < n) {
                    int cur = sum[GetIdx(i + 1, j + 1)] + val;
                    int cnt = path[GetIdx(i + 1, j + 1)];
                    update(cur, cnt, &score, &route);
                }

                sum[idx] = score < 0 ? INT_MIN : score;
                path[idx] = route;
            }
        }

        return vector<int>{sum[GetIdx(0, 0)] == INT_MIN ? 0 : sum[GetIdx(0, 0)],
                        sum[GetIdx(0, 0)] == INT_MIN ? 0 : path[GetIdx(0, 0)]};  
    }

 private:
    static const int mod = 1000000007;
    int n;


    void ToMatrix(const vector<string>& board, vector<vector<char>>& matrix) {
        for (const string& str : board) {
            vector<char> tmp;
            for (char c : str) {
                tmp.push_back(c);
            }
            matrix.push_back(tmp);
        }
    }

    int GetIdx(int x, int y) {
        return x * n + y;
    }

    pair<int, int> ParseIdx(int idx) {
        return pair<int, int>(idx / n, idx % n);
    }
    
    // 更新值
    void update(int cur, int cnt, int *score, int *route) {
        // 如果当前值大于 score，更新score，
        if (cur > *score) {
            *score = cur;
            *route = cnt;
        } else if (cur == *score && cur != INT_MIN) {   // 如果当前值等于 score，只更新路径，
            *route += cnt;
        }
        *route %= mod;
    }
};
`````

