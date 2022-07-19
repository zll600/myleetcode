# [[NOIP2006 提高组] 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

## 题目描述

金明今天很开心，家里购置的新房就要领钥匙了，新房里有一间金明自己专用的很宽敞的房间。更让他高兴的是，妈妈昨天对他说：“你的房间需要购买哪些物品，怎么布置，你说了算，只要不超过 $n$ 元钱就行”。今天一早，金明就开始做预算了，他把想买的物品分为两类：主件与附件，附件是从属于某个主件的，下表就是一些主件与附件的例子：

|  主件  |      附件      |
| :----: | :------------: |
|  电脑  | 打印机，扫描仪 |
|  书柜  |      图书      |
|  书桌  |   台灯，文具   |
| 工作椅 |       无       |

如果要买归类为附件的物品，必须先买该附件所属的主件。每个主件可以有 $0$ 个、$1$ 个或 $2$ 个附件。每个附件对应一个主件，附件不再有从属于自己的附件。金明想买的东西很多，肯定会超过妈妈限定的 $n$ 元。于是，他把每件物品规定了一个重要度，分为 $5$ 等：用整数 $1 \sim 5$ 表示，第 $5$ 等最重要。他还从因特网上查到了每件物品的价格（都是 $10$ 元的整数倍）。他希望在不超过 $n$ 元的前提下，使每件物品的价格与重要度的乘积的总和最大。

设第 $j$ 件物品的价格为 $v_j$，重要度为$w_j$，共选中了 $k$ 件物品，编号依次为 $j_1,j_2,\dots,j_k$，则所求的总和为：

$v_{j_1} \times w_{j_1}+v_{j_2} \times w_{j_2}+ \dots +v_{j_k} \times w_{j_k}$。

请你帮助金明设计一个满足要求的购物单。

## 输入格式

第一行有两个整数，分别表示总钱数 $n$ 和希望购买的物品个数 $m$。

第 $2$ 到第 $(m + 1)$ 行，每行三个整数，第 $(i + 1)$ 行的整数 $v_i$，$p_i$，$q_i$ 分别表示第 $i$ 件物品的价格、重要度以及它对应的的主件。如果 $q_i=0$，表示该物品本身是主件。

## 输出格式

输出一行一个整数表示答案。

## 样例 #1

### 样例输入 #1

```
1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0
```

### 样例输出 #1

```
2200
```

## 提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 3.2 \times 10^4$，$1 \leq m \leq 60$，$0 \leq v_i \leq 10^4$，$1 \leq p_i \leq 5$，$0 \leq q_i \leq m$，答案不超过 $2 \times 10^5$。

### 解题思路

看到题目，价格，重要度，给定总钱数要求价值最大，还是很容易看出来一点 01 背包的，这道题目难点在于状态转移不太好想

一般 01 背包，到 i 位置为止，这个位置选或者不选

但是这道题目中 **附件** 的选择的情况受到 **主件** 的限制，所以状态转移为复杂一点，详情可以参考题解区大佬的分析

- 不选这个主件
- 选择这个主件，且只选主件
- 选择这个主件，且选择附件 1
- 选择这个主件，且选择附件 2
- 选择这个主件，且选择附件 1 和 2

具体状态转移可以参考代码，这个代码有些 case 是没有通过的，还是有点问题，不过思路应该就是这样了

### Solution 1: Dynamic Programming



````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(int n, int m, vector<int>& main_values, vector<int>& main_weights,
            vector<vector<int>> & appendix_values, vector<vector<int>>& appendix_weights) {
        vector<int> dp(n + 1, 0);
        
        for (int i = 0; i < m; ++i) {
            for (int j = n; main_weights[i] > 0 && j >= main_weights[i]; --j) {
                dp[j] = max(dp[j], dp[j - main_weights[i]] + main_values[i]);
                
                if (j >= main_weights[i] + appendix_weights[i][1]) {
                    dp[j] = max(dp[j], dp[j - main_weights[i] - appendix_weights[i][1]] + main_values[i] + appendix_values[i][1]);
                }
                if (j >= main_weights[i] + appendix_values[i][2]) {
                    dp[j] = max(dp[j], dp[j - main_weights[i] - appendix_weights[i][2]] + main_values[i] + appendix_values[i][2]);
                }
                
                if (j >= main_weights[i] + appendix_weights[i][1] + appendix_weights[i][2]) {
                    dp[j] = max(dp[j], dp[j - main_weights[i] - appendix_weights[i][1] - appendix_weights[i][2]]
                            + main_weights[i] + appendix_values[i][1] + appendix_values[i][2]);
                }
            }
        }
        cout << dp[n] << endl;
    }
};

int main(void) {
    int n, m;
    cin >> n >> m;
    
    vector<int> main_values(m, 0);
    vector<int> main_weights(m, 0);
    vector<vector<int>> appendix_values(m, vector<int>(3, 0));
    vector<vector<int>> appendix_weights(m, vector<int>(3, 0));
    
    int value, weight, is_main;
    for (int i = 0; i < m; ++i) {
        cin >> weight >> value >> is_main;
        
        if (!is_main) {
            main_weights[i] = weight;
            main_values[i] = value * weight;
        } else {
            ++appendix_weights[is_main][0];
            
            appendix_weights[is_main][appendix_weights[i][0]] = weight;
            appendix_values[is_main][appendix_weights[i][0]] = value * weight;
        }
    }
    
    Solution obj;
    obj.Solve(n, m, main_values, main_weights, appendix_values, appendix_weights);
    
    return 0;
}
````

