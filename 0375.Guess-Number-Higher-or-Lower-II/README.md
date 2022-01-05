# [375. Guess Number Higher or Lower II](https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/)

We are playing the Guessing Game. The game will work as follows:

1. I pick a number between `1` and `n`.
2. You guess a number.
3. If you guess the right number, **you win the game**.
4. If you guess the wrong number, then I will tell you whether the number I picked is **higher or lower**, and you will continue guessing.
5. Every time you guess a wrong number `x`, you will pay `x` dollars. If you run out of money, **you lose the game**.

Given a particular `n`, return *the minimum amount of money you need to **guarantee a win regardless of what number I pick***.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/10/graph.png)

```
Input: n = 10
Output: 16
Explanation: The winning strategy is as follows:
- The range is [1,10]. Guess 7.
    - If this is my number, your total is $0. Otherwise, you pay $7.
    - If my number is higher, the range is [8,10]. Guess 9.
        - If this is my number, your total is $7. Otherwise, you pay $9.
        - If my number is higher, it must be 10. Guess 10. Your total is $7 + $9 = $16.
        - If my number is lower, it must be 8. Guess 8. Your total is $7 + $9 = $16.
    - If my number is lower, the range is [1,6]. Guess 3.
        - If this is my number, your total is $7. Otherwise, you pay $3.
        - If my number is higher, the range is [4,6]. Guess 5.
            - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $5.
            - If my number is higher, it must be 6. Guess 6. Your total is $7 + $3 + $5 = $15.
            - If my number is lower, it must be 4. Guess 4. Your total is $7 + $3 + $5 = $15.
        - If my number is lower, the range is [1,2]. Guess 1.
            - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $1.
            - If my number is higher, it must be 2. Guess 2. Your total is $7 + $3 + $1 = $11.
The worst case in all these scenarios is that you pay $16. Hence, you only need $16 to guarantee a win.
```

**Example 2:**

```
Input: n = 1
Output: 0
Explanation: There is only one possible number, so you can guess 1 and not have to pay anything.
```

**Example 3:**

```
Input: n = 2
Output: 1
Explanation: There are two possible numbers, 1 and 2.
- Guess 1.
    - If this is my number, your total is $0. Otherwise, you pay $1.
    - If my number is higher, it must be 2. Guess 2. Your total is $1.
The worst case is that you pay $1.
```

 

**Constraints:**

- `1 <= n <= 200`

## 题目大意

我们正在玩一个猜数游戏，游戏规则如下：

1. 我从 1 到 n 之间选择一个数字。
2. 你来猜我选了哪个数字。
3. 如果你猜到正确的数字，就会 赢得游戏 。
4. 如果你猜错了，那么我会告诉你，我选的数字比你的 更大或者更小 ，并且你需要继续猜数。
5. 每当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。如果你花光了钱，就会 输掉游戏 。



给你一个特定的数字 n ，返回能够 确保你获胜 的最小现金数，不管我选择任何数

## 解题思路

刚开始觉得这道题目是一道 二分的题目，但是利用二分确实好像没办法求解，但又发现存在重复子问题，所以可以考虑使用递归来求解，这道题目可以参考这篇题解：https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/solution/xiang-xi-fen-xi-cong-di-gui-dao-ji-yi-hu-9qun/

* 要考虑区间中的任何一个值都可能水最终的结果
* 最终结果是最小的



### Solution 1:  记忆化递归(TLE)

这种解法，可以参考这篇题解：https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/solution/wei-rao-li-lun-jian-ming-ji-yi-hua-sou-s-jv1c/

对范围`[left, right]` 进行递归，枚举中间值 `i`，将整个区间划分为 `[left, i - 1],[i + 1, right]` ，去这两者中的最大值，整个枚举过程取最小值

````c++
class Solution {
public:
    int getMoneyAmount(int n) {
        unordered_map<pair<int, int>, int, PairHash> memo; // 缓存
        return DFS(1, n, memo);
    }
    
 private:
    // 提供散列函数
    struct PairHash {
        template<typename T1, typename T2>
        size_t operator()(const pair<T1, T2>& elem) const {
            auto h1 = hash<T1>{}(elem.first);
            auto h2 = hash<T2>{}(elem.second);
            return h1 ^ h2;
        }
    };
    
    
    
    int DFS(int left, int right, unordered_map<pair<int, int>, int, PairHash>& memo) {
        if (left >= right) {
            // 递归终止条件
            return 0;
        }
        
        pair<int, int> key = make_pair(left, right);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int res = INT_MAX;
        for (int i = left; i <= right; ++i) {
            // 状态转移
            // 在 [left, i - 1] 和 [i + 1, right] 中选最大的
            // 在当前选最小的
            res = min(res, max(DFS(left, i - 1, memo), DFS(i + 1, right, memo)) + i);
        }
        memo[key] = res; // 更新缓存
        return res;
    }   
};
````

### Solution 2: DP

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/solution/xiang-xi-fen-xi-cong-di-gui-dao-ji-yi-hu-9qun/

强烈建议看看这篇题解，

这种解法就是非常著名的区间 dp问题，还可以看下这篇题解：https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/solution/gong-shui-san-xie-yi-ti-shuang-jie-ji-yi-92e5/



````c++
class Solution {
public:
    int getMoneyAmount(int n) {
        // 状态定义 dp[i][j]表示 [i, j]的答案
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
        
        for (int len = 1; len <= n; ++len) { // 枚举长度
            int i = 1, j = len;
            while (j <= n) {
                if (i == j) { // 猜那个都对
                    dp[i][j] = 0;
                } else if (i + 1 >= j) { // 只会错一次
                    dp[i][j] = i;
                } else if (i + 2 >= j) { // 利用二分的话，先猜中间，最多就猜个中间
                    dp[i][j] = i + 1;
                } else {
                    // 其余位置，枚举所有可能
                    for (int m = i + 1; m < j; ++m) {
                        // 这里需要防止溢出
                        dp[i][j] = min(1L * dp[i][j], 1L * max(dp[i][m - 1], dp[m + 1][j]) + m);
                    }
                }
                
                // 向右下进行遍历
                ++i;
                ++j;
            }
        }
        return dp[1][n];
    }
};
````
