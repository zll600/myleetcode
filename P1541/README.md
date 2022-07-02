# [[NOIP2010 提高组] 乌龟棋](https://www.luogu.com.cn/problem/P1541)

## 题目背景

小明过生日的时候，爸爸送给他一副乌龟棋当作礼物。

## 题目描述

乌龟棋的棋盘是一行$N$个格子，每个格子上一个分数（非负整数）。棋盘第1格是唯一的起点，第$N$格是终点，游戏要求玩家控制一个乌龟棋子从起点出发走到终点。


乌龟棋中$M$张爬行卡片，分成4种不同的类型（$M$张卡片中不一定包含所有$4$种类型的卡片，见样例），每种类型的卡片上分别标有$1,2,3,4$四个数字之一，表示使用这种卡片后，乌龟棋子将向前爬行相应的格子数。游戏中，玩家每次需要从所有的爬行卡片中选择一张之前没有使用过的爬行卡片，控制乌龟棋子前进相应的格子数，每张卡片只能使用一次。


游戏中，乌龟棋子自动获得起点格子的分数，并且在后续的爬行中每到达一个格子，就得到该格子相应的分数。玩家最终游戏得分就是乌龟棋子从起点到终点过程中到过的所有格子的分数总和。


很明显，用不同的爬行卡片使用顺序会使得最终游戏的得分不同，小明想要找到一种卡片使用顺序使得最终游戏得分最多。


现在，告诉你棋盘上每个格子的分数和所有的爬行卡片，你能告诉小明，他最多能得到多少分吗？

## 输入格式

每行中两个数之间用一个空格隔开。

第$1$行$2$个正整数$N,M$，分别表示棋盘格子数和爬行卡片数。


第$2$行$N$个非负整数，$a_1,a_2,…,a_N$，其中$a_i$表示棋盘第$i$个格子上的分数。


第$3$行$M$个整数，$b_1,b_2,…,b_M$，表示M张爬行卡片上的数字。


输入数据保证到达终点时刚好用光$M$张爬行卡片。

## 输出格式

$1$个整数，表示小明最多能得到的分数。

## 样例 #1

### 样例输入 #1

```
9 5
6 10 14 2 8 8 18 5 17
1 3 1 2 1
```

### 样例输出 #1

```
73
```

## 提示

每个测试点$1s$

小明使用爬行卡片顺序为$1,1,3,1,2$,得到的分数为$6+10+14+8+18+17=73$。注意，由于起点是$1$，所以自动获得第$1$格的分数$6$。


对于$30\%$的数据有$1≤N≤30,1≤M≤12$。


对于$50\%$的数据有$1≤N≤120,1≤M≤50$，且$4$种爬行卡片，每种卡片的张数不会超过$20$。


对于$100\%$的数据有$1≤N≤350,1≤M≤120$，且$4$种爬行卡片，每种卡片的张数不会超过$40$；$0≤a_i≤100,1≤i≤N,1≤b_i≤4,1≤i≤M$。



### Solution 1: DFS + Memory

使用 DFS + 记忆化搜索

这里的状态其实开始应该是定义为在到了 位置 i 时，使用了 n1 张 1，和 n2 张 2，和 n3 张 3，和 n4 张 4 的分数，但是通过使用卡片数，可以算出位置这一维度，那么就可以进行降维来计算



````c++
#include <bits/stdc++.h>

using namespace std;

const int kLen = 120;

class Solution  {
 public:
    void Solve(vector<int>& board, vector<int>& cards) {
        vector<vector<vector<vector<int>>>> cache(kLen, vector<vector<vector<int>>>(kLen, vector<vector<int>>(kLen, vector<int>(kLen, 0))));
        
        cout <<  DFS(board, cards, 0, 0, 0, 0, cache) + board[0] << endl;
    }
    
 private:
    int DFS(vector<int>& board, vector<int> cards, int n1, int n2, int n3, int n4,
            vector<vector<vector<vector<int>>>>& cache) {
        if (cache[n1][n2][n3][n4]) {
            return cache[n1][n2][n3][n4];
        }
        if (n1 == cards[1] && n2 == cards[2] && n3 == cards[3] && n4 == cards[4]) {
            return 0;
        }
        
        int pos = n1 * 1 + n2 * 2 + n3 * 3 + n4 * 4;
        int res = 0;
        if (n1 < cards[1]) {
            res = max(res, DFS(board, cards, n1 + 1, n2, n3, n4, cache) + board[pos + 1]);
        }
        if (n2 < cards[2]) {
            res = max(res, DFS(board, cards, n1, n2 + 1, n3, n4, cache) + board[pos + 2]);
        }
        if (n3 < cards[3]) {
            res = max(res, DFS(board, cards, n1, n2, n3 + 1, n4, cache) + board[pos + 3]);
        }
        if (n4 < cards[4]) {
            res = max(res, DFS(board, cards, n1, n2, n3, n4 + 1, cache) + board[pos + 4]);
        }
        
        cache[n1][n2][n3][n4] = res;
        return res;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> board(n);
    for (int i = 0; i < n; ++i) {
        cin >> board[i];
        // cout << board[i] << " ";
    }
    // cout << endl;
    
    vector<int> cards(5);
    for (int i = 0; i < m; ++i) {
        int tmp;
        cin >> tmp;
        // cout << tmp << " ";
        ++cards[tmp];
    }
    // cout << endl;
    
    Solution obj;
    obj.Solve(board, cards);

    return 0;
}
````



### Solution 2: DP

将上面的记忆化搜索该一下，就可以得到dp 的解法



````c++
#include <bits/stdc++.h>

using namespace std;

const int kLen = 120;

class Solution  {
 public:
    void Solve(vector<int>& board, vector<int>& cards) {
        vector<vector<vector<vector<int>>>> dp(kLen, vector<vector<vector<int>>>(kLen, vector<vector<int>>(kLen, vector<int>(kLen, 0))));
        dp[0][0][0][0] = board[0];
        
        int ans = board[0];
        for (int n1 = 0; n1 <= cards[1]; ++n1) {
            for (int n2 = 0; n2 <= cards[2]; ++n2) {
                for (int n3 = 0; n3 <= cards[3]; ++n3) {
                    for (int n4 = 0; n4 <= cards[4]; ++n4) {
                        int pos = n1 * 1 + n2 * 2 + n3 * 3 + n4 * 4;
                        
                        if (n1 != 0) {
                            dp[n1][n2][n3][n4] = max(dp[n1][n2][n3][n4], dp[n1 - 1][n2][n3][n4] + board[pos]);
                        }
                        if (n2 != 0) {
                            dp[n1][n2][n3][n4] = max(dp[n1][n2][n3][n4], dp[n1][n2 - 1][n3][n4] + board[pos]);
                        }
                        if (n3 != 0) {
                            dp[n1][n2][n3][n4] = max(dp[n1][n2][n3][n4], dp[n1][n2][n3 - 1][n4] + board[pos]);
                        }
                        if (n4 != 0) {
                            dp[n1][n2][n3][n4] = max(dp[n1][n2][n3][n4], dp[n1 - 1][n2][n3][n4 - 1] + board[pos]);
                        }
                        
                        ans = max(ans, dp[n1][n2][n3][n4]);
                    }
                }
            }
        }
        cout << ans << endl;
    }

};

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> board(n);
    for (int i = 0; i < n; ++i) {
        cin >> board[i];
        // cout << board[i] << " ";
    }
    // cout << endl;
    
    vector<int> cards(5);
    for (int i = 0; i < m; ++i) {
        int tmp;
        cin >> tmp;
        // cout << tmp << " ";
        ++cards[tmp];
    }
    // cout << endl;
    
    Solution obj;
    obj.Solve(board, cards);

    return 0;
}
````

