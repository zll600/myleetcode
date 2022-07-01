# [【XR-2】奇迹](https://www.luogu.com.cn/problem/P5440)

## 题目背景

> 相信奇迹的人，本身就和奇迹一样了不起。——笛亚 《星游记》

## 题目描述

我们称一个**日期**为一个八位数，第 1~4 位构成年，第 5~6 位构成月，第 7~8 位构成日，不足位数用 0 补足。同时，要求日期所代表的这一天真实存在，且年的范围为 1~9999。

出现奇迹的日期都存在相同的特点：由“日”组成的两位数，由“月+日”组成的四位数，由“年+月+日”组成的八位数均为**质数**。但并不是所有存在这样特点的日期都一定会出现奇迹。

现在，你得到了一个可能会出现奇迹的日期，然而不幸的是这个日期却是残缺的，八位中可能有若干位无法确定。你需要知道这个日期有多少种可能，这样你才能做好充足的准备去迎接奇迹的到来。

## 输入格式

**本题有多组数据。**

第一行一个正整数 $T$，表示数据组数。

接下来的 $T$ 行，每行一个八位字符串。其中第 $i$ 位如果为 `-`，则表示日期的第 $i$ 位无法确定，否则表示日期的第 $i$ 位为字符串中第 $i$ 位上的数字。

## 输出格式

对每组数据，一行一个整数，表示答案。

## 样例 #1

### 样例输入 #1

```
2
53-7-3-7
20190629
```

### 样例输出 #1

```
6
0
```

## 提示

【样例 $1$ 说明】

`53-7-3-7` 的 $6$ 种可能的日期如下：

```plain
53070307
53070317
53170307
53370307
53570317
53770307
```

【数据规模与约定】

一共 $10$ 个测试点，记 $c$ 为八位字符串中 `-` 的个数。

对前 $9$ 个测试点，在第 $i$ 个测试点中保证 $c = i - 1$。

对 $100\%$ 的数据保证 $1 \le T \le 10$。



### Solution 1:

这里放的是别人的代码，和我的思路比较像，我的代码无法通过

````c++
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int n, a[9], prim[10005], flag[10005], tot;
char tmpc;
int p10[]= {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
int yue[]= {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
inline void init() {
	flag[1]= 1;
	for(int i= 2; i < 10005; i++) {
		if(!flag[i]) prim[++tot]= i;
		for(int j= 1; j <= tot; j++) {
			if(i * prim[j] >= 10005) break;
			flag[i * prim[j]]= 1;
			if(i % prim[j] == 0) break;
		}
	}
	return;
}
inline int pdrn(int x) {
	return (x % 4 == 0 && x % 100 != 0) || (x % 400 == 0 && x % 3200 != 0);
}
inline int pdzs(int x) {
	if(x < 2) return 0;
	for(int i= 1; i <= tot; i++)
		if(x % prim[i] == 0) return x == prim[i];
	return 1;
}
int dfs(int nown, int num, int rn, int jy) {
	if(nown == 0) {
		if(num / 10000 == 0) return 0;
		if(rn && pdrn(num / 10000) == 0) return 0;
		return pdzs(num);
	}
	if(nown == 6) {
		if(num == 0 || num > 31 || !pdzs(num)) return 0;
		if(num == 31) jy= 1;
	}
	if(nown == 4) {
		if(num < 32 || num > 1231 || !pdzs(num)) return 0;
		if(jy && !yue[num / 100]) return 0;
		if(num / 100 == 2) {
			if(num % 100 > 29) return 0;
			if(num % 100 == 29) rn= 1;
		}
	}
	if(a[nown] != -1) return dfs(nown - 1, a[nown] * p10[8 - nown] + num, rn, jy);
	int res= 0;
	for(int i= 0; i <= 9; i++) res+= dfs(nown - 1, i * p10[8 - nown] + num, rn, jy);
	return res;
}
char get() {
	char ch= getchar();
	while((ch < '0' || ch > '9') && ch != '-') ch= getchar();
	return ch;
}
void put(int x) {
	if(x > 9) put(x / 10);
	putchar('0' + x % 10);
	return;
}
int main() {
	init(), cin >> n;
	while(n--) {
		for(int i= 1; i <= 8; i++) tmpc= get(), a[i]= (tmpc == '-' ? -1 : tmpc - '0');
		put(dfs(8, 0, 0, 0)), putchar('\n');
	}
	return 0;
}
````

