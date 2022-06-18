# [【模板】快速幂||取余运算](https://www.luogu.com.cn/problem/P1226)

## 题目描述

给你三个整数 $a,b,p$，求 $a^b \bmod p$。

## 输入格式

输入只有一行三个整数，分别代表 $a,b,p$。

## 输出格式

输出一行一个字符串 `a^b mod p=s`，其中 $a,b,p$ 分别为题目给定的值， $s$ 为运算结果。

## 样例 #1

### 样例输入 #1

```
2 10 9
```

### 样例输出 #1

```
2^10 mod 9=7
```

## 提示

**样例解释**

$2^{10} = 1024$，$1024 \bmod 9 = 7$。

**数据规模与约定**

对于 $100\%$ 的数据，保证 $0\le a,b < 2^{31}$，$a+b>0$，$2 \leq p \lt 2^{31}$。



### Solution 1:

矩阵快速幂模板

````c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int QuickPower(ll a, ll b, ll p) {
    ll ans = 1, base = a;
    while (b > 0) {
        if (b & 1) {
            ans *= base;
            ans %= p;
        }
        base *= base;
        base %= p;
        b >>= 1;
    }
    return ans % p;
}

int main(void) {
    ll a, b, p;
    cin >> a >> b >> p;
    
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, QuickPower(a, b, p));
    
    return 0;
}
````

