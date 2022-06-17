# [[NOIP1998 提高组] 拼数](https://www.luogu.com.cn/problem/P1012)

## 题目描述

设有 $n$ 个正整数 $a_1 \dots a_n$，将它们联接成一排，相邻数字首尾相接，组成一个最大的整数。

## 输入格式

第一行有一个整数，表示数字个数 $n$。

第二行有 $n$ 个整数，表示给出的 $n$ 个整数 $a_i$。

## 输出格式

一个正整数，表示最大的整数

## 样例 #1

### 样例输入 #1

```
3
13 312 343
```

### 样例输出 #1

```
34331213
```

## 样例 #2

### 样例输入 #2

```
4
7 13 4 246
```

### 样例输出 #2

```
7424613
```

## 提示

对于全部的测试点，保证 $1 \leq n \leq 20$，$1 \leq a_i \leq 10^9$。


## 解题思路

这道题目其实就是考察对 *字典序* 的理解，这里需要注意的是想 321 和 32 这种情况，需要将 32 放在后面

### Solution 1:

````c++
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    int n;
    cin >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; ++i) {
        long cur;
        cin >> cur;
        strs[i] = to_string(cur);
    }

    sort(strs.begin(), strs.end(), [](const string& lhs, const string& rhs) {
        return lhs + rhs < rhs + lhs;
    });
    string res;
    for (int i = n - 1; i >= 0; --i) {
        res += strs[i];
    }
    cout << stoll(res) << endl;

    return 0;
}
````

