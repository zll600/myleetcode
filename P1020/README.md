# [[NOIP1999 普及组] 导弹拦截](https://www.luogu.com.cn/problem/P1020)

## 题目描述

某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度，但是以后每一发炮弹都不能高于前一发的高度。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。


输入导弹依次飞来的高度（雷达给出的高度数据是 $ \le 50000$ 的正整数），计算这套系统最多能拦截多少导弹，如果要拦截所有导弹最少要配备多少套这种导弹拦截系统。

## 输入格式

一行，若干个整数（个数 $ \le 100000$）

NOIP 原题数据规模不超过 $2000$。

## 输出格式

两行，每行一个整数，第一个数字表示这套系统最多能拦截多少导弹，第二个数字表示如果要拦截所有导弹最少要配备多少套这种导弹拦截系统。

## 样例 #1

### 样例输入 #1

```
389 207 155 300 299 170 158 65
```

### 样例输出 #1

```
6
2
```

## 提示

为了让大家更好地测试 $\mathcal{O}(n^2)$ 算法，本题开启 spj，$\mathcal{O}(n^2)$ 算法 $100$ 分，$\mathcal{O}(n\log n)$ 算法 $200$ 分。

每点两问，按问给分。



### 解题思路

两个问题

- 最长不上升子序列

- 能够覆盖该数列的最长不上升子序列个数的最小值。

### Solution 1: DP

解决最长不上升子序列，时间复杂度 `O(n^2)`，`dp[i]` 表示选择第 i 个位置的最长不上升子序列的长度，

则有以下两种情况

- 第 i 项作为新的子序列的第一项 `dp[i] = 1`
- 第 i 项作为之前一个子序列的最后一项 `dp[i] = max(dp[i]. dp[j] + 1), 0 <= j < i`



解决能覆盖该数列的最长不上升子序列个数的最小值，时间复杂度 `O(nlogn)` ，这里也利用贪心的思想，从左向右遍历数组，对于每个高度，查找已经存在的 大于等于的第一个高度，然后做替换，如果找不到，就新插入一个，不过这里是使用头插的做法，数组的没一项表示这个系统可以拦截的最大高度

````c++
#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
    void Solve(vector<int>& nums) {
        Process1(nums);
        Process2(nums);
    }
    
 private:
    void Process1(vector<int>& nums) {
        const int len = nums.size();
        vector<int> dp(len, 0);
        dp[0] = 1;
        
        int ans = dp[0];
        for (int i = 1; i < len; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[i] <= nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            // cout << dp[i] << endl;
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
    }
    
    void Process2(vector<int>& nums) {
        const int len = nums.size();
        vector<int> systems;
        systems.push_back(nums[0]);
        
        for (int i = 1; i < len; ++i) {
            int low = 0, high = systems.size() - 1;
            
            while (low < high) {
                const int mid = low + (high - low + 1) / 2;
                
                if (systems[mid] >= nums[i]) {
                    low = mid;
                } else {
                    high = mid - 1;
                }
            }
            
            if (systems[high] >= nums[i]) {
                systems[high] = nums[i];
            } else {
                systems.insert(systems.begin(), nums[i]);
            }
        }
        cout << systems.size() << endl;
    }
    
 private:
    const int kMod = 1e9 + 7;
};

int main(void) {
    vector<int> nums(50000);
    
    int i = 0;
    int tmp;
    while (cin >> tmp) {
        // cout << tmp << endl;
        nums[i] = tmp;
        ++i;
    }
    nums.resize(i);
    
    Solution obj;
    obj.Solve(nums);
    
    return 0;
}
````



### Solution 2:



````c++

````

