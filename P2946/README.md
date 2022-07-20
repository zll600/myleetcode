# [[USACO09MAR]Cow Frisbee Team S](https://www.luogu.com.cn/problem/P2946)

## 题目描述

老唐最近迷上了飞盘，约翰想和他一起玩，于是打算从他家的 $N$ 头奶牛中选出一支队伍。

每只奶牛的能力为整数，第 $i$ 头奶牛的能力为$R_i$ 。飞盘队的队员数量不能少于 $1$、大于$N$。一支队伍的总能力就是所有队员能力的总和。

约翰比较迷信，他的幸运数字是 $F$ ，所以他要求队伍的总能力必须是 $F$ 的倍数。请帮他

算一下，符合这个要求的队伍组合有多少？由于这个数字很大，只要输出答案对 $10^8$ 取模的值。

## 输入格式

第一行：两个用空格分开的整数：$N$ 和 $F$。

第二行到 $N+1$ 行：第 $i+1$ 行有一个整数$R_i$ ，表示第 $i$ 头奶牛的能力。

## 输出格式

第一行：单个整数，表示方案数对 $10^8$ 取模的值。

## 样例 #1

### 样例输入 #1

```
4 5 
1 
2 
8 
2
```

### 样例输出 #1

```
3
```

## 提示

#### 数据范围与约定

- 对于 $100\%$ 的数据，$1 \le N \le 2000$，$1 \le F \le 1000$ ，$1 \le R_i \le 10^5$ 。



### 题目大意

这是一道 01 背包类型的题目，状态可以定义为第 i 个选或者不选的时候，能力和 mod f 为 j 的方案数，状态转移为

不选择第 i 个，那么 `dp[i][j] = dp[i - 1][j]`

选择第 i 个，那么 `dp[i][j] = dp[i - 1][(j - values[i] + f) % f]`

### Solution 1:



````c++
#include <bits/stdc++.h>

using namespace std;

static const int kMod = 10e8;

class Solution {
 public:
    void Solve(int n, int f, vector<int>& values) {
        vector<vector<int>> dp(n, vector<int>(1001, 0));
        
        
        for (int i = 0; i < n; ++i) {
            dp[i][values[i]] = 1;
        }
        
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 1000; ++j) {
                dp[i][j] = ((dp[i][j] + dp[i - 1][j]) % kMod + dp[i - 1][(j - values[i] + f) % f]) % kMod;
            }
        }
        
        cout << dp[n - 1][0] << endl;
    }
};

int main(void) {
    int n, f;
    cin >> n >> f;
    
    vector<int> values(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
        values[i] %= f;
    }
    
    Solution obj;
    obj.Solve(n, f, values);
    
    return 0;
}
````
