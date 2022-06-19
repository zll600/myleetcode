# [NOIP1998 普及组] 幂次方

## 题目描述

任何一个正整数都可以用 $2$ 的幂次方表示。例如 $137=2^7+2^3+2^0 $。

同时约定方次用括号来表示，即 $a^b$ 可表示为 $a(b)$。

由此可知，$137$ 可表示为 $2(7)+2(3)+2(0)$

进一步：

$7= 2^2+2+2^0$  ( $2^1$ 用 $2$ 表示)，并且 $3=2+2^0$。

所以最后 $137$ 可表示为 $2(2(2)+2+2(0))+2(2+2(0))+2(0)$。

又如 $1315=2^{10} +2^8 +2^5 +2+1$

所以 $1315$ 最后可表示为 $2(2(2+2(0))+2)+2(2(2+2(0)))+2(2(2)+2(0))+2+2(0)$。

## 输入格式

一行一个正整数 $n$。

## 输出格式

符合约定的 $n$ 的 $0, 2$ 表示（在表示中不能有空格）。

## 样例 #1

### 样例输入 #1

```
1315
```

### 样例输出 #1

```
2(2(2+2(0))+2)+2(2(2+2(0)))+2(2(2)+2(0))+2+2(0)
```

## 提示

**【数据范围】**

对于 $100\%$ 的数据，$1 \le n \le 2 \times {10}^4$。



### Solution 1: DFS

- 找到大于且最接近当前数的2 的幂
- 如果幂值是 0 或者 2，那么直接输出
- 如果幂值大于 2，那么对 幂值做 DFS
- 将当前数减去小于且最接近的 2 的幂，对剩余部分继续递归

````c++
#include <bits/stdc++.h>

using namespace std;

void Search(int num) {
    if (num <= 0) {
        return;
    }   

    cout << 2;
    int val = 1, exp = 0;
    while (num >= val) {
        val *= 2;
        ++exp;
    }   
    --exp;
    if (exp == 0 || exp == 2) {
        cout << "(" << exp << ")";
    }   
    
    if (exp >= 3) {
        cout << "(";
        Search(exp);
        cout << ")";
    }   
    num -= val / 2;
    if (num) {
        cout << "+";
        Search(num);
    }   
}

int main(void) {
    int num;
    cin >> num;
    
    Search(num);
    cout << endl;
    
    return 0;
}
````
