# [[USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)

## 题目描述

观察下面的数字金字塔。


写一个程序来查找从最高点到底部任意处结束的路径，使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。

```cpp
        7 
      3   8 
    8   1   0 
  2   7   4   4 
4   5   2   6   5 
```
在上面的样例中,从 $7 \to 3 \to 8 \to 7 \to 5$ 的路径产生了最大

## 输入格式

第一个行一个正整数 $r$ ,表示行的数目。

后面每行为这个数字金字塔特定行包含的整数。

## 输出格式

单独的一行,包含那个可能得到的最大的和。

## 样例 #1

### 样例输入 #1

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
```

### 样例输出 #1

```
30
```

## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le r \le 1000$，所有输入在 $[0,100]$ 范围内。

题目翻译来自NOCOW。

USACO Training Section 1.5

IOI1994 Day1T1



### Solution 1: Recursion

这道题目的子问题还是比较容易看出来，然后利用记忆化搜索就可以 ac 了

````c++
#include <bits/stdc++.h>

using namespace std;

class Solution  {
 public:
    void Solve(vector<vector<int>>& data, vector<vector<int>>& cache) {
        cout << DFS(data, 0, 0, cache);
    }
    
 private:
    
 
    int DFS(const vector<vector<int>>& grid, int i, int j, vector<vector<int>>& cache) {
        if (i == grid.size()) {
            return 0;
        }
        
        if (cache[i][j] != -1) {
            return cache[i][j];
        }
        
        int left = DFS(grid, i + 1, j, cache);
        int right = DFS(grid, i + 1, j + 1, cache);
        
        cache[i][j] = max(left, right) + grid[i][j];
        return cache[i][j];
    }
};

int main(void) {
    int n;
    cin >> n;
    
    vector<vector<int>> data(n);
    vector<vector<int>> cache(n);
    for (int i = 0; i < n; ++i) {
        int tmp;
        for (int j = 0; j <= i; ++j) {
            cin >> tmp;
            data[i].push_back(tmp);
            cache[i].push_back(-1);
        }
    }
    
    Solution obj;
    obj.Solve(data, cache);

    return 0;
}
````

