# [通天之分组背包](https://www.luogu.com.cn/problem/P1757)

## 题目背景

直达通天路·小 A 历险记第二篇

## 题目描述

自 $01$ 背包问世之后，小 A 对此深感兴趣。一天，小 A 去远游，却发现他的背包不同于 $01$ 背包，他的物品大致可分为 $k$ 组，每组中的物品相互冲突，现在，他想知道最大的利用价值是多少。

## 输入格式

两个数 $m,n$，表示一共有 $n$ 件物品，总重量为 $m$。

接下来 $n$ 行，每行 $3$ 个数 $a_i,b_i,c_i$，表示物品的重量，利用价值，所属组数。

## 输出格式

一个数，最大的利用价值。

## 样例 #1

### 样例输入 #1

```
45 3
10 10 1
10 5 1
50 400 2
```

### 样例输出 #1

```
10
```

## 提示

$1 \leq m, n \leq 1000$。



### Solution 1: 01 back pack

这道题目就是在 01 背包的基础上再加上一个分组的前提，状态转移方程还是一样的，同样可以进行状态压缩，



````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(int n, int m, int max_group, vector<int> values, vector<int> weights,
            vector<int> buckets, vector<vector<int>>& groups) {
        vector<int> dp(m + 1, 0);
        
        int ans = 0;
        // groups
        for (int g = 0; g < max_group; ++g) {
            // weights
            for (int i = 0; i < buckets[g]; ++i) {
                int idx = groups[g][i];
                for (int j = m; j >= weights[idx]; --j) {
                    dp[j] = max(dp[j], dp[j - weights[idx]] + values[idx]);
                }
            }
        }
        cout << dp[m] << endl;
    }
};

int main(void) {
    int m, n;
    cin >> m >> n;
    // value
    vector<int> values(n, 0);
    // weights
    vector<int> weights(n, 0);
    // the count of specific group
    vector<int> buckets(n, 0);
    
    int max_group = 0;
    // specific elem of group to global sequence
    vector<vector<int>> groups(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        int group = 0;
        cin >> weights[i] >> values[i] >> group;
        groups[group][buckets[group]] = i;
        
        ++buckets[group];
        max_group = max(max_group, group);
    }
    
    Solution obj;
    obj.Solve(n, m, max_group, values, weights, buckets, groups);
    
    return 0;
}
````

