# [1575. Count All Possible Routes](https://leetcode.com/problems/count-all-possible-routes/)

## 题目

You are given an array of **distinct** positive integers locations where `locations[i]` represents the position of city `i`. You are also given integers `start`, `finish` and `fuel` representing the starting city, ending city, and the initial amount of fuel you have, respectively.

At each step, if you are at city `i`, you can pick any city `j` such that `j != i` and `0 <= j < locations.length` and move to city `j`. Moving from city `i` to city `j` reduces the amount of fuel you have by `|locations[i] - locations[j]|`. Please notice that `|x|` denotes the absolute value of `x`.

Notice that `fuel` **cannot** become negative at any point in time, and that you are **allowed** to visit any city more than once (including `start` and `finish`).

Return *the count of all possible routes from* `start` *to* `finish`.

Since the answer may be too large, return it modulo `10^9 + 7`.

 

**Example 1:**

```
Input: locations = [2,3,6,8,4], start = 1, finish = 3, fuel = 5
Output: 4
Explanation: The following are all possible routes, each uses 5 units of fuel:
1 -> 3
1 -> 2 -> 3
1 -> 4 -> 3
1 -> 4 -> 2 -> 3
```

**Example 2:**

```
Input: locations = [4,3,1], start = 1, finish = 0, fuel = 6
Output: 5
Explanation: The following are all possible routes:
1 -> 0, used fuel = 1
1 -> 2 -> 0, used fuel = 5
1 -> 2 -> 1 -> 0, used fuel = 5
1 -> 0 -> 1 -> 0, used fuel = 3
1 -> 0 -> 1 -> 0 -> 1 -> 0, used fuel = 5
```

**Example 3:**

```
Input: locations = [5,2,1], start = 0, finish = 2, fuel = 3
Output: 0
Explanation: It's impossible to get from 0 to 2 using only 3 units of fuel since the shortest route needs 4 units of fuel.
```

**Example 4:**

```
Input: locations = [2,1,5], start = 0, finish = 0, fuel = 3
Output: 2
Explanation: There are two possible routes, 0 and 0 -> 1 -> 0.
```

**Example 5:**

```
Input: locations = [1,2,3], start = 0, finish = 2, fuel = 40
Output: 615088286
Explanation: The total number of possible routes is 2615088300. Taking this number modulo 10^9 + 7 gives us 615088286.
```

 

**Constraints:**

- `2 <= locations.length <= 100`
- `1 <= locations[i] <= 10^9`
- All integers in `locations` are **distinct**.
- `0 <= start, finish < locations.length`
- `1 <= fuel <= 200`

## 题目大意

给定一个互不相同的正整数数组，数组的每一项 location[i] 代表第 i 个城市，同时给定 start，finish 和fuel 分别表示出发城市，目的城市和初始的油量，

每一步，如果你在城市 i 你可以选择任意一个城市 j，满足 j != i, 且 0 <= j < locations.length, 并移动到城市 J，从城市 i 移动到城市 j ,消耗的汽油量

为|location[i] - locations[j]|, |x| 表示 绝对值，

请你返回从 start 到 finish 所有可能路径的数目，

## 解题思路

* 可以用记忆化搜索，状态改变的是当前的位置，和剩余的油量
* 也可以用 DP 来解决，
* 记忆

## 代码

`````c++
/*
class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int size = locations.size();
        // -1 表示该种情况还没有计算过，0 表示该种情况下的路径数为 0
        vector<vector<int>> cache(size, vector<int>(fuel + 1, -1));
        
        return DFS(locations, start, finish, fuel, cache);
    }
    
 private:
    
    static const int mod = 1000000007;

    int DFS(const vector<int>& locations, int cur, int finish,
            int fuel, vector<vector<int>>& cache) {
        // 如果缓存中已经有答案直接返回
        if (cache[cur][fuel] != -1) {
            return cache[cur][fuel];
        } 
        
        // 如果剩余油量为零，且不能到达目标位置，
        // if (fuel == 0 && cur != finish) {
            // cache[cur][fuel] = 0;
            // return 0;
        // }
        
        int size = locations.size();
        
        // 如果剩余油量不为0，但无法到达任何位置
        // bool has_next = false;
        // for (int i = 0; i < size; ++i) {
            // if (i != cur) {
                // int need = abs(locations[i] - locations[cur]);
                // if (fuel >= need) {
                    // has_next = true;
                    // break;
                // }
            // }
        // }
        // if (fuel != 0 && !has_next) {
            // cache[cur][fuel] = cur == finish ? 1 : 0;
            // return cache[cur][fuel];
        // }
        
        // 如果一步到不了，那么多于一步肯定到不了
        int need = abs(locations[finish] - locations[cur]);
        if (fuel < need) {
            cache[cur][fuel] = 0;
            return 0;
        }
        
        int sum = cur == finish ? 1 : 0;
        for (int i = 0; i < size; ++i) {
            if (i != cur) {
                int need = abs(locations[i] - locations[cur]);
                if (fuel >= need) {
                    sum += DFS(locations, i, finish, fuel - need, cache);
                    sum %= mod;
                }
            }
        }
        cache[cur][fuel] = sum;
        return sum;
    }
};*/

// DP
class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int size = locations.size();
        vector<vector<int>> dp(size, vector<int>(fuel + 1, 0));
        
        for (int i = 0; i <= fuel; ++i) {
            dp[finish][i] = 1;
        }
        
        // fuel 和 fuel-need 具有严格的大小关系，，因此需要从小到达枚举油量
        for (int i = 0; i <= fuel; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    if (j != k) {
                        int need = abs(locations[j] - locations[k]);
                        if (need <= i) {
                            dp[j][i] += dp[k][i - need];
                            dp[j][i] %= mod;
                        }
                    }
                }
            }
        }
        return dp[start][fuel];
    }
 private:
    static const int mod = 1000000007;
};
`````

