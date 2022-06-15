# [[NOIP2011 普及组] 数字反转](https://www.luogu.com.cn/problem/P1307)

## 题目描述

给定一个整数，请将该数各个位上数字反转得到一个新数。新数也应满足整数的常见形式，即除非给定的原数为零，否则反转后得到的新数的最高位数字不应为零（参见样例2）。

## 输入格式

一个整数 $N$

## 输出格式

一个整数，表示反转后的新数。

## 样例 #1

### 样例输入 #1

```
123
```

### 样例输出 #1

```
321
```

## 样例 #2

### 样例输入 #2

```
-380
```

### 样例输出 #2

```
-83
```

## 提示

数据范围

$-1,000,000,000≤N≤1,000,000,000 $。

noip2011普及组第一题

## 解题思路

简单模拟一下就可以了

### Solution 1:


````c++
#include <iostream>

using namespace std;

int Flip(int num) {
    int ans = 0;
    while (num > 0) {
        ans = ans * 10 + num % 10;
        num /= 10;
    }
    return ans;
}

void Solve(int num) {
    if (num == 0) {
        cout << num << endl;
        return;
    }

    int ans = 0;
    if (num < 0) {
        ans = -1 * Flip(-1 * num);
    } else {
        ans = Flip(num);
    }
    cout << ans << endl;
}

int main(void) {
    int num;
    cin >> num;

    Solve(num);

    return 0;
}
````

