# [[NOIP2006 普及组] 开心的金明](https://www.luogu.com.cn/problem/P1060)

## 题目描述

金明今天很开心，家里购置的新房就要领钥匙了，新房里有一间他自己专用的很宽敞的房间。更让他高兴的是，妈妈昨天对他说：“你的房间需要购买哪些物品，怎么布置，你说了算，只要不超过$N$元钱就行”。今天一早金明就开始做预算，但是他想买的东西太多了，肯定会超过妈妈限定的$N$元。于是，他把每件物品规定了一个重要度，分为$5$等：用整数$1-5$表示，第$5$等最重要。他还从因特网上查到了每件物品的价格（都是整数元）。他希望在不超过$N$元（可以等于$N$元）的前提下，使每件物品的价格与重要度的乘积的总和最大。

设第$j$件物品的价格为$v[j]$，重要度为$w[j]$，共选中了$k$件物品，编号依次为$j_1,j_2,…,j_k$，则所求的总和为：

$v[j_1] \times w[j_1]+v[j_2] \times w[j_2]+ …+v[j_k] \times w[j_k]$。

请你帮助金明设计一个满足要求的购物单。

## 输入格式

第一行，为$2$个正整数，用一个空格隔开：$n,m$（其中$N(<30000)$表示总钱数，$m(<25)$为希望购买物品的个数。）

从第$2$行到第$m+1$行，第$j$行给出了编号为$j-1$的物品的基本数据，每行有$2$个非负整数$ v p$（其中$v$表示该物品的价格$(v \le 10000)$，$p$表示该物品的重要度($1-5$)

## 输出格式

$1$个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值$(<100000000)$。

## 样例 #1

### 样例输入 #1

```
1000 5
800 2
400 5
300 5
400 3
200 2
```

### 样例输出 #1

```
3900
```

## 提示

NOIP 2006 普及组 第二题



### Solution 1: dp

这道题目就是 `01 背包` 的模板题目

状态定义： `dp[i][j]` 表示使用到第  i 个物品，且有 j 数目的金钱的时候可以得到的最大总和

状态转移：`dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - commodities[i][0]] + commodities[i][0] * commodities[i][1])`

初始化：初始化dp 数组的第一行

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(vector<vector<int>>& commodities, int T) {
        const int len = commodities.size();
        vector<vector<int>> dp(len, vector<int>(T, 0));
        
        for (int j = 1; j <= T;  ++j) {
            if (j >= commodities[0][0]) {
                dp[0][j] = commodities[0][1];
            }
        }
        
        for (int i = 1; i < len; ++i) {
            for (int j = 1; j <= T; ++j) {
                dp[i][j] = dp[i - 1][j];
                
                if (j >= commodities[i][0]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - commodities[i][0]] + commodities[i][1]);
                }
            }
        }
        cout << dp[len - 1][T] << endl;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> commodities(m, vector<int>(2, 0));
    for (int i = 0; i < m; ++i) {
        cin >> commodities[i][0] >> commodities[i][1];
        commodities[i][1] *= commodities[i][0];
    }
    
    Solution obj;
    obj.Solve(commodities, n);
    
    return 0;
}
````

