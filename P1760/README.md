# [通天之汉诺塔](https://www.luogu.com.cn/problem/P1760)

## 题目背景

直达通天路·小A历险记第四篇

## 题目描述

在你的帮助下，小A成功收集到了宝贵的数据，他终于来到了传说中连接通天路的通天山。但是这距离通天路仍然有一段距离，但是小A突然发现他没有地图！！！但是幸运的是，他在山脚下发现了一个宝箱。根据经验判断（小A有经验吗？），地图应该就在其中！在宝箱上，有三根柱子以及在一根柱子上的n个圆盘。小A在经过很长时间判断后，觉得这就是hanoi塔！（这都要琢磨）。但是移动是需要时间的，所以小A必须要通过制造延寿药水来完成这项任务。现在，他请你告诉他需要多少步完成，以便他造足够的延寿药水.。时限1s。

## 输入格式

一个数n，表示有n个圆盘

## 输出格式

一个数s，表示需要s步。

## 样例 #1

### 样例输入 #1

```
31
```

### 样例输出 #1

```
2147483647
```

## 样例 #2

### 样例输入 #2

```
15
```

### 样例输出 #2

```
32767
```

## 提示

对于所有数据n<=15000

很容易的练手题哦！



### Solution 1: Recursion

状态转移如下:

- 将 n -  1 个盘子从 a 移动到 b
- 将 a 上最大的盘子移动到 c
- 将 b 上 n - 1 个盘子移动到 c 

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution  {
 public:
    void Solve(int n) {
        DFS(n, 1, 2, 3);
        cout << ans_ << endl;
    }
    
 private:
    int ans_ = 0;
    
    void DFS(int n, int a, int b, int c) {
        // base case
        if (n == 0) {
            return;
        }
        
        // move n - 1 from a to b by using c
        DFS(n - 1, a, b, c);
        ++ans_;
        // move n - 1 from b to c by using a
        DFS(n - 1, b, c, a);
    }
};

int main(void) {
    int n;
    cin >> n;
    
    Solution obj;
    obj.Solve(n);

    return 0;
}
````



### Recurrence

将 递归改为 递推来做

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution  {
 public:
    void Solve(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1 + dp[i - 1];
        }
        cout << dp[n] << endl;
    }
};

int main(void) {
    int n;
    cin >> n;
    
    Solution obj;
    obj.Solve(n);

    return 0;
}
````



### Formula



````python
n=int(input())
print (pow(2,n)-1)
````

