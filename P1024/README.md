# [[NOIP2001 提高组] 一元三次方程求解](https://www.luogu.com.cn/problem/P1024)

## 题目描述

有形如：$a x^3 + b x^2 + c x + d = 0$  这样的一个一元三次方程。给出该方程中各项的系数（$a,b,c,d$ 均为实数），并约定该方程存在三个不同实根（根的范围在 $-100$ 至 $100$ 之间），且根与根之差的绝对值 $\ge 1$。要求由小到大依次在同一行输出这三个实根(根与根之间留有空格)，并精确到小数点后 $2$ 位。

提示：记方程 $f(x) = 0$，若存在 $2$ 个数 $x_1$ 和 $x_2$，且 $x_1 < x_2$，$f(x_1) \times f(x_2) < 0$，则在 $(x_1, x_2)$ 之间一定有一个根。

## 输入格式

一行，$4$ 个实数 $a, b, c, d$。

## 输出格式

一行，$3$ 个实根，从小到大输出，并精确到小数点后 $2$ 位。

## 样例 #1

### 样例输入 #1

```
1 -5 -4 20
```

### 样例输出 #1

```
-2.00 2.00 5.00
```

## 提示

**【题目来源】**

NOIP 2001 提高组第一题



### Solution 1: Binary Search

这道题目是参考别人的代码改的，因为这里浮点数的判断始终是个问题，没办法ac

总的思路就是枚举每一个长度为 1 的区间，然后二分查找解，如果找到就输出，找完就结束，这里的记录返回值其实没必要，一元三次方程，最多三个解，没有必要多那一步

````c++
#include <bits/stdc++.h>

using namespace std;

int get() {
	int x = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f = -1; c = getchar();
	}
	
	while(isdigit(c)) {
		x = x * 10 + c - '0'; c = getchar();
	}
	return x * f;
}

class Solution {
 public:
	void Solve(int a, int b, int c, int d) {
		int s= 0;
		for (int i = -100; i < 100; ++i) {
			double l=i; 
        double r=i+1;
        double x1=Calc(a, b, c, d, l); 
        double x2=Calc(a, b, c, d, r);
        if(!x1) 
        {
            printf("%.2lf ",l); 
            s++;
        }      //判断左端点，是零点直接输出。
                        
                        //不能判断右端点，会重复。
        if(x1*x2<0)                             //区间内有根。
        {
            while(r-l>=0.001)                     //二分控制精度。
            {
                double m=(l+r)/2;  //middle
                if(Calc(a, b, c, d, m) * Calc(a, b, c, d, r)<=0) 
                   l=m; 
                else 
                   r=m;   //计算中点处函数值缩小区间。
            }
            printf("%.2lf ",r);  
            //输出右端点。
            s++;
        }
        if (s==3) 
            break;             
            //找到三个就退出大概会省一点时间
		}
	}
	
 private:
	double Calc(int a, int b, int c, int d, double val) {
		return a * val * val * val + b * val * val + c * val + d;
	}
};

int main(void) {
	int a = get(), b = get(), c = get(), d = get();
	Solution obj;
	obj.Solve(a, b, c, d);
	
	return 0;
}
````

