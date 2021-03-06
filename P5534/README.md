# [【XR-3】等差数列](https://www.luogu.com.cn/problem/P5534)

## 题目描述

小 X 给了你一个等差数列的前两项以及项数，请你求出这个等差数列各项之和。

等差数列：对于一个 $n$ 项数列 $a$，如果满足对于任意 $i \in [1,n)$，有 $a_{i+1} - a_i = d$，其中 $d$ 为定值，则称这个数列为一个等差数列。

## 输入格式

一行 $3$ 个整数 $a_1, a_2, n$，表示等差数列的第 $1,2$ 项以及项数。

**数据范围：**

- $|a_1|,|a_2| \le 10^6$。
- $3 \le n \le 10^6$。

## 输出格式

一行一个整数，表示答案。

## 样例 #1

### 样例输入 #1

```
1 2 3
```

### 样例输出 #1

```
6
```

## 样例 #2

### 样例输入 #2

```
-5 -10 5
```

### 样例输出 #2

```
-75
```

## 提示

【样例 $1$ 说明】

这个等差数列为 `1 2 3`，其各项之和为 $6$。



## 解题思路

这道题目考察的就是等差数列的相关知识，这里重点在学习两个求和公式

- Sn = (a1 + an) * n/2
- Sn = a1 * n + n * (n - 1) * diff / 2





### Solution 1:

这里还有一点需要注意的就是乘法溢出的问题

````c++
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    int a1, a2, n;
    cin >> a1 >> a2 >> n;
    int diff = a2 - a1;
    
    cout << 1LL * a1 * n + 1LL * n * (n - 1) * diff / 2 << endl;
    
    return 0;
}
````

