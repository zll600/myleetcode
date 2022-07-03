# [饥饿的奶牛](https://www.luogu.com.cn/problem/P1868)

## 题目描述

有一条奶牛冲出了围栏，来到了一处圣地（对于奶牛来说），上面用牛语写着一段文字。

现用汉语翻译为：

有 $N$ 个区间，每个区间 $x,y$ 表示提供的 $x\sim y$ 共 $y-x+1$ 堆优质牧草。你可以选择任意区间但不能有重复的部分。

对于奶牛来说，自然是吃的越多越好，然而奶牛智商有限，现在请你帮助他。

## 输入格式

第一行一个整数 $N$。

接下来 $N$ 行，每行两个数 $x,y$，描述一个区间。

## 输出格式

输出最多能吃到的牧草堆数。

## 样例 #1

### 样例输入 #1

```
3
1 3
7 8
3 4
```

### 样例输出 #1

```
5
```

## 提示

$1 \leq n \leq 1.5 \times 10^5$，$0 \leq x \leq y \leq 3 \times 10^6$。



### Solution 1: DP





`````c++
#include <bits/stdc++.h>

using namespace std;

const int kLen = 120;

class Solution  {
 public:
    void Solve(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs[0] == rhs[0]) {
                return lhs[1] < rhs[1];
            }
            return lhs[0] < rhs[0];
        });
        
        const int bound = intervals.back().back();
        const int len = intervals.size();
        
        int ans = 0;
        int idx = 0;
        vector<int> dp(bound + 1, 0);
        for (int i = 0; i <= bound; ++i) {
            if (i > 0) {
                dp[i] = max(dp[i], dp[i - 1]);
            }
            
            while (idx < len && intervals[idx][0] == i) {
                dp[intervals[idx][1]] = max(dp[intervals[idx][1]], dp[intervals[idx][0] - 1] + intervals[idx][1] - intervals[idx][0] + 1);
                ++idx;
            }
            ans = max(ans, dp[i]);
        }
        cout << ans << endl;
    }
};

int main(void) {
    int m;
    cin >> m;
    vector<vector<int>> intervals(m, vector<int>(2, 0));
    for (int i = 0; i < m; ++i) {
        cin >> intervals[i][0] >> intervals[i][1];
    }
    
    Solution obj;
    obj.Solve(intervals);

    return 0;
}
`````

