# [[NOIP2001 普及组] 数的计算](https://www.luogu.com.cn/problem/P1028)

## 题目描述

我们要求找出具有下列性质数的个数（包含输入的正整数 $n$）。

先输入一个正整数 $n$（$n \le 1000$），然后对此正整数按照如下方法进行处理：

1. 不作任何处理；

2. 在它的左边拼接一个正整数，但该正整数不能超过原数，或者是上一个被拼接的数的一半；

3. 加上数后，继续按此规则进行处理，直到不能再加正整数为止。

## 输入格式

一行，一个正整数 $n$（$n \le 1000$）。

## 输出格式

一个整数，表示具有该性质数的个数。

## 样例 #1

### 样例输入 #1

```
6
```

### 样例输出 #1

```
6
```

## 提示

**【样例解释】**

满足条件的数为：$6$，$16$，$26$，$126$，$36$，$136$。

**【题目来源】**

NOIP 2001 普及组第一题

### Soluion 1: DFS(TLE)

````c++
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    vector<int> buckets(10001);
    int n;
    cin >> n;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            buckets[i] += buckets[j];
        }
        ++buckets[i];
    }
    cout << buckets[n] << endl;
    return 0;
}
````

### Solution 2: DP

````c++
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    vector<int> buckets(10001);
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            buckets[i] += buckets[j];
        }
        ++buckets[i];
    }
    cout << buckets[n] << endl;
    return 0;
}
````
