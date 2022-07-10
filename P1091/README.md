# [[NOIP2004 提高组] 合唱队形](https://www.luogu.com.cn/problem/P1091)

## 题目描述

$n$ 位同学站成一排，音乐老师要请其中的 $n-k$ 位同学出列，使得剩下的 $k$ 位同学排成合唱队形。

合唱队形是指这样的一种队形：设 $k$ 位同学从左到右依次编号为 $1,2,$ … $,k$，他们的身高分别为 $t_1,t_2,$ … $,t_k$，则他们的身高满足 $t_1< \cdots <t_i>t_{i+1}>$ … $>t_k(1\le i\le k)$。

你的任务是，已知所有 $n$ 位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。

## 输入格式

共二行。

第一行是一个整数 $n$（$2\le n\le100$），表示同学的总数。

第二行有 $n$ 个整数，用空格分隔，第 $i$ 个整数 $t_i$（$130\le t_i\le230$）是第 $i$ 位同学的身高（厘米）。

## 输出格式

一个整数，最少需要几位同学出列。

## 样例 #1

### 样例输入 #1

```
8
186 186 150 200 160 130 197 220
```

### 样例输出 #1

```
4
```

## 提示

对于 $50\%$ 的数据，保证有 $n \le 20$。

对于全部的数据，保证有 $n \le 100$。



### Solution 1:

这道题目求删掉的最少的人，那么反过来，只要尽可能保留多的人就可以了



这道题目可以分解为求解两个dp 的题目，

- 求得以第 i 个结尾的最长上升（严格）子序列，
- 求得以第 i 个开头的最长下降（严格）子序列

可以这样想的原因是，题目已经给出了状态转移方程



````c++
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
    void Solve(vector<int>& nums) {
        const int len = nums.size();
        
        
        // Longest ascending subsequence
        vector<int> dp1(len, 1);
        // dp1[0] = 1;
        for (int i = 1; i < len; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp1[i] = max(dp1[i], dp1[j] + 1);
                }
            }
        }
        
        // Longest descending subsequence
        vector<int> dp2(len, 1);
        // dp2[len - 1] = 1;
        for (int i = len - 2; i >= 0; --i) {
            for (int j = len - 1; j > i; --j) {
                if (nums[i] > nums[j]) {
                    dp2[i] = max(dp2[i], dp2[j] + 1);
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < len; ++i) {
            ans = max(ans, dp1[i] + dp2[i] - 1);
        }
        cout << len - ans << endl;
    }
    
 private:
    
};

int main(void) {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    
    Solution obj;
    obj.Solve(nums);
    
    return 0;
}
````

