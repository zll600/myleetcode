# [[NOIP2001 提高组] 数的划分](https://www.luogu.com.cn/problem/P1025)

## 题目描述

将整数 $n$ 分成 $k$ 份，且每份不能为空，任意两个方案不相同（不考虑顺序）。

例如：$n=7$，$k=3$，下面三种分法被认为是相同的。

$1,1,5$;   
$1,5,1$;   
$5,1,1$.

问有多少种不同的分法。

## 输入格式

$n,k$ （$6<n \le 200$，$2  \le k  \le  6$）

## 输出格式

$1$ 个整数，即不同的分法。

## 样例 #1

### 样例输入 #1

```
7 3
```

### 样例输出 #1

```
4
```

## 提示

四种分法为：  
$1,1,5$;  
$1,2,4$;  
$1,3,3$;  
$2,2,3$.

**【题目来源】**

NOIP 2001 提高组第二题



### Solution 1: DFS

这里使用的是 DFS 加剪枝来做的，具体就是本来每棵子树都是一棵 k 叉树，但是其实根据累加的 cur 值和 target 之间的关系可以做一些剪枝优化

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
    void Solve(int n, int k) {
        DFS(n, 1, 0, k);
        cout << ans_ << endl;
    }
    
 private:
    int ans_ = 0;
    
    void DFS(int target, int idx, int cur, int k) {
        if (k == 0) {
            if (cur == target) {
                ++ans_;
            }
            return;
        }
        
        for (int i = idx; cur + i * k <= target; ++i) {
            DFS(target, i, cur + i, k - 1);
        }
    }
};

int main() {
    int n, k;
    cin >> n >> k;

    Solution obj;
    obj.Solve(n, k);
    return 0;
}

````

