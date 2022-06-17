# [[NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)

## 题目描述

已知 $n$ 个整数 $x_1,x_2,\cdots,x_n$，以及 $1$ 个整数 $k$（$k<n$）。从 $n$ 个整数中任选 $k$ 个整数相加，可分别得到一系列的和。例如当 $n=4$，$k=3$，$4$ 个整数分别为 $3,7,12,19$ 时，可得全部的组合与它们的和为：

$3+7+12=22$

$3+7+19=29$

$7+12+19=38$

$3+12+19=34$

现在，要求你计算出和为素数共有多少种。

例如上例，只有一种的和为素数：$3+7+19=29$。

## 输入格式

第一行两个空格隔开的整数 $n,k$（$1 \le n \le 20$，$k<n$）。

第二行 $n$ 个整数，分别为 $x_1,x_2,\cdots,x_n$（$1 \le x_i \le 5\times 10^6$）。

## 输出格式

输出一个整数，表示种类数。

## 样例 #1

### 样例输入 #1

```
4 3
3 7 12 19
```

### 样例输出 #1

```
1
```

## 提示

**【题目来源】**

NOIP 2002 普及组第二题



### Solution 1: DFS

这道题目就是一道排列组合题目



画出递归树，树的最大高度就是 `k + 1`，每个位置都可以选或者不选



````c++
#include <iostream>
#include <vector>

using namespace std;

class Solution {       
 public:               
    int AllWays(const vector<int> nums, int idx, int total, int left) {
        if (left == 0) {
            return IsPrime(total) ? 1 : 0; 
        }                                                                                                                                                                
                                                                                                                                                                         
        int ans = 0;                                                                                                                                                     
        for (size_t i = idx; i < nums.size(); ++i) {
            ans += AllWays(nums, i + 1, total + nums[i], left - 1);                                                                                                      
        }                              
        return ans;                    
    }                                  
                                       
 private:                              
    int ans_;                          
                                       
    bool IsPrime(int num) {            
        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {        
                return false;          
            }                          
        }                              
        return true;                   
    }                                  
};

int main(void) {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    Solution obj;
    cout << obj.AllWays(nums, 0, 0, k) << endl;
    return 0;
}
````



