# [808. Soup Servings](https://leetcode-cn.com/problems/soup-servings/)

There are two types of soup: **type A** and **type B**. Initially, we have `n` ml of each type of soup. There are four kinds of operations:

1. Serve `100` ml of **soup A** and `0` ml of **soup B**,
2. Serve `75` ml of **soup A** and `25` ml of **soup B**,
3. Serve `50` ml of **soup A** and `50` ml of **soup B**, and
4. Serve `25` ml of **soup A** and `75` ml of **soup B**.

When we serve some soup, we give it to someone, and we no longer have it. Each turn, we will choose from the four operations with an equal  probability `0.25`. If the remaining volume of soup is not  enough to complete the operation, we will serve as much as possible. We  stop once we no longer have some quantity of both types of soup.

**Note** that we do not have an operation where all `100` ml's of **soup B** are used first.

Return *the probability that **soup A** will be empty first, plus half the probability that **A** and **B** become empty at the same time*. Answers within `10-5` of the actual answer will be accepted.

 

**Example 1:**

```
Input: n = 50
Output: 0.62500
Explanation: If we choose the first two operations, A will become empty first.
For the third operation, A and B will become empty at the same time.
For the fourth operation, B will become empty first.
So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
```

**Example 2:**

```
Input: n = 100
Output: 0.71875
```

 

**Constraints:**

- `0 <= n <= 109`

## 题目大意

有 `A` 和 `B` 两种类型 的汤。一开始每种类型的汤有 `n` 毫升。有四种分配操作：

- 提供 `100ml` 的 `汤A` 和 `0ml` 的 `汤B` 
- 提供 `75ml` 的 `汤A` 和 `25ml` 的 `汤B` 
- 提供 `50ml` 的 `汤A` 和 `50ml` 的 `汤B` 
- 提供 `25ml` 的 `汤A` 和 `75ml` 的 `汤B`

当我们把汤分配给某人之后，汤就没有了。

每个回合，我们将从四种概率同为 `0.25` 的操作中进行分配选择。如果汤的剩余量不足以完成某次操作，我们将尽可能分配。当两种类型的汤都分配完时，停止操作。

注意 不存在先分配 `100 ml` `汤B` 的操作。

需要返回的值： 汤A 先分配完的概率 +  汤A和汤B 同时分配完的概率 / 2。返回值在正确答案 10-5 的范围内将被认为是正确的。

## 解题思路


### Solution 1:

这道题目可以参考 [这篇题解](https://leetcode.com/problems/soup-servings/)

这里根据题目所给的状态转移的条件，做一个简化，因为每次变化的基本单位都是 25 ml，所以这了直接将A,B 的总容量除以 25,并向上取整，

这样每次状态转移的单位就是 1了，

````c++
class Solution {
public:
    double soupServings(int n) {
        if (n >= 4800) {
            return 1;
        }
        
        int m = static_cast<int>(ceil(n / 25.0));
        // dp[i][j] 表示 a 先消耗完 加上 a，b 同时消耗完的概率
        vector<vector<double>> dp(m + 1, vector<double>(m + 1, 0.0));
        // a，b 同时消耗完
        dp[0][0] = 0.5;
        // 初始化第一行和第一列
        for (int i = 1; i <= m; ++i) {
            dp[i][0] = 0.0;
            dp[0][i] = 1.0;
        }
        
        // 状态转移
        for (int i = 1; i <= m; ++i) {
            int a1 = i > 4 ? i - 4 : 0;
            int a2 = i > 3 ? i - 3 : 0;
            int a3 = i > 2 ? i - 2 : 0;
            int a4 = i > 1 ? i - 1 : 0;
            
            for (int j = 1; j <= m; ++j) {
                int b1 = j;
                int b2 = j - 1 > 0 ? j - 1 : 0;
                int b3 = j - 2 > 0 ? j - 2 : 0;
                int b4 = j - 3 > 0 ? j - 3 : 0;
                
                dp[i][j] = 0.25 * (dp[a1][b1] + dp[a2][b2] + dp[a3][b3] + dp[a4][b4]);
            }
        }
        
        return dp[m][m];
    }
};
````
