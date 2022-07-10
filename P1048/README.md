# [[NOIP2005 普及组] 采药](https://www.luogu.com.cn/problem/P1048)

## 题目描述

辰辰是个天资聪颖的孩子，他的梦想是成为世界上最伟大的医师。为此，他想拜附近最有威望的医师为师。医师为了判断他的资质，给他出了一个难题。医师把他带到一个到处都是草药的山洞里对他说：“孩子，这个山洞里有一些不同的草药，采每一株都需要一些时间，每一株也有它自身的价值。我会给你一段时间，在这段时间里，你可以采到一些草药。如果你是一个聪明的孩子，你应该可以让采到的草药的总价值最大。”


如果你是辰辰，你能完成这个任务吗？

## 输入格式

第一行有 $2$ 个整数 $T$（$1 \le T \le 1000$）和 $M$（$1 \le  M \le 100$），用一个空格隔开，$T$ 代表总共能够用来采药的时间，$M$ 代表山洞里的草药的数目。

接下来的 $M$ 行每行包括两个在 $1$ 到 $100$ 之间（包括 $1$ 和 $100$）的整数，分别表示采摘某株草药的时间和这株草药的价值。

## 输出格式

输出在规定的时间内可以采到的草药的最大总价值。

## 样例 #1

### 样例输入 #1

```
70 3
71 100
69 1
1 2
```

### 样例输出 #1

```
3
```

## 提示

**【数据范围】**

- 对于 $30\%$ 的数据，$M \le 10$；
- 对于全部的数据，$M \le 100$。

**【题目来源】**

NOIP 2005 普及组第三题



### Solution 1: Recursion

递归，每中草药选或者不选，保留最大价值即可

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(vector<vector<int>>& plants, int T) {
        DFS(plants, 0, 0, T);
        cout << ans << endl;
    }
    
 private:
    int ans = 0;
    
    void DFS(const vector<vector<int>>& plants, int idx, int cur, int T) {
        if (idx == plants.size()) {
            // cout << endl;
            ans = max(ans, cur);
            return;
        }
        // cout << " - ";
        
        DFS(plants, idx + 1, cur, T);
        if (T >= plants[idx][0]) {
            // cout << plants[idx][1];
            DFS(plants, idx + 1, cur + plants[idx][1], T - plants[idx][0]);
        }
    }
};

int main(void) {
    int T, M;
    cin >> T >> M;
    
    vector<vector<int>> plants(M, vector<int>(2, 0));
    for (int i = 0; i < M; ++i) {
        cin >> plants[i][0] >> plants[i][1];
    }
    
    Solution obj;
    obj.Solve(plants, T);
    
    return 0;
}
````



### Solution 2:

这里利用返回值来记录整个递归的过程，不再使用 ans 变量

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(vector<vector<int>>& plants, int T) {
        cout << DFS(plants, 0, T);
    }
    
 private:
    int ans = 0;
    
    int DFS(const vector<vector<int>>& plants, int idx, int T) {
        if (idx == plants.size()) {
            // cout << endl;
            return 0;
        }
        // cout << " - ";
        
        int res1= DFS(plants, idx + 1, T);
        int res2 = INT_MIN;
        if (T >= plants[idx][0]) {
            // cout << plants[idx][1];
            res2 = DFS(plants, idx + 1, T - plants[idx][0]) + plants[idx][1];
        }
        return max(res1, res2);
    }
};

int main(void) {
    int T, M;
    cin >> T >> M;
    
    vector<vector<int>> plants(M, vector<int>(2, 0));
    for (int i = 0; i < M; ++i) {
        cin >> plants[i][0] >> plants[i][1];
    }
    
    Solution obj;
    obj.Solve(plants, T);
    
    return 0;
}
````



### Solution 3: Memory + DFS

使用记忆花递归，可以通过

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(vector<vector<int>>& plants, int T) {
        vector<vector<int>> mem(101, vector<int>(1001, -1));
        cout << DFS(plants, 0, T, mem);
    }
    
 private:
    int ans = 0;
    
    int DFS(const vector<vector<int>>& plants, int idx, int T,
            vector<vector<int>>& mem) {
        if (idx == plants.size()) {
            // cout << endl;
            return 0;
        }
        
        if (mem[idx][T] != -1) {
            return mem[idx][T];
        }
        
        int res1= DFS(plants, idx + 1, T, mem);
        int res2 = INT_MIN;
        if (T >= plants[idx][0]) {
            // cout << plants[idx][1];
            res2 = DFS(plants, idx + 1, T - plants[idx][0], mem) + plants[idx][1];
        }
        mem[idx][T] = max(res1, res2);
    
        return mem[idx][T];            
    }
};

int main(void) {
    int T, M;
    cin >> T >> M;
    
    vector<vector<int>> plants(M, vector<int>(2, 0));
    for (int i = 0; i < M; ++i) {
        cin >> plants[i][0] >> plants[i][1];
    }
    
    Solution obj;
    obj.Solve(plants, T);
    
    return 0;
}
````



### Solution 3: 01 Backpack

根据记忆化搜索可以很方便的得出状态定义和状态转移方程

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(vector<vector<int>>& plants, int T) {
        const int len = plants.size();
        vector<vector<int>> dp(len, vector<int>(T + 1, 0));
        
        for (int j = 1; j <= T; ++j) {
            if (j >= plants[0][0]) {
                dp[0][j] = plants[0][1];
            }
            // cout << dp[0][j] << " ";
        }
        // cout << endl;
        
        for (int i = 1; i < len; ++i) {
            for (int j = 1; j <= T; ++j) {
                dp[i][j] = dp[i - 1][j];
                
                if (j >= plants[i][0]) {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - plants[i][0]] + plants[i][1]);
                }
            
                // cout << dp[i][j] << " ";
            }
            // cout << endl;
        }
        
        cout << dp[len - 1][T] << endl;
    }
};

int main(void) {
    int T, M;
    cin >> T >> M;
    
    vector<vector<int>> plants(M, vector<int>(2, 0));
    for (int i = 0; i < M; ++i) {
        cin >> plants[i][0] >> plants[i][1];
    }
    
    Solution obj;
    obj.Solve(plants, T);
    
    return 0;
}
````



### Solution 1: dp 

状态压缩后的动态规划

`````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(vector<vector<int>>& plants, int T) {
        const int len = plants.size();
        vector<int> dp(T + 1, 0);
        
        for (int j = 1;j <= T; ++j) {
            if (j >= plants[0][0]) {
                dp[j] = plants[0][1];
            }
        }
        
        for (int i = 1; i < len; ++i) {
            for (int j = T; j >= plants[i][0]; --j) {
                dp[j] = max(dp[j], dp[j - plants[i][0]] + plants[i][1]);
                // cout << dp[j] << " ";
            }
            // cout << endl;
        }
        
        cout << dp[T] << endl;
    }
};

int main(void) {
    int T, M;
    cin >> T >> M;
    
    vector<vector<int>> plants(M, vector<int>(2, 0));
    for (int i = 0; i < M; ++i) {
        cin >> plants[i][0] >> plants[i][1];
    }
    
    Solution obj;
    obj.Solve(plants, T);
    
    return 0;
}
`````

