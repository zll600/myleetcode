# [464. Can I Win](https://leetcode-cn.com/problems/can-i-win/)

## 题目

In the "100 game" two players take turns adding, to a running total, any integer from `1` to `10`. The player who first causes the running total to **reach or exceed** 100 wins.

What if we change the game so that players **cannot** re-use integers?

For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.

Given two integers `maxChoosableInteger` and `desiredTotal`, return `true` if the first player to move can force a win, otherwise, return `false`. Assume both players play **optimally**.

 

**Example 1:**

```
Input: maxChoosableInteger = 10, desiredTotal = 11
Output: false
Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
```

**Example 2:**

```
Input: maxChoosableInteger = 10, desiredTotal = 0
Output: true
```

**Example 3:**

```
Input: maxChoosableInteger = 10, desiredTotal = 1
Output: true
```

 

**Constraints:**

- `1 <= maxChoosableInteger <= 20`
- `0 <= desiredTotal <= 300`

## 题目大意

在“100 game” 这个游戏中，两名玩家轮流从 1 和 10 中选出一个数累加入加和，谁第一个让累加和达到或者超过 100，谁就获得胜利

如果将游戏规则改为，玩家不能重复使用数字，

例如，两个玩家可以轮流从公共整数池中抽取从 1 到 15 的整数（不放回），直到累计整数和 >= 100。

给定一个整数 maxChoosableInteger （整数池中可选择的最大数）和另一个整数 desiredTotal（累计和），判断先出手的玩家是否能稳赢（假设两位玩家游戏时都表现最佳）

## 解题思路

这道题可以联系 石子游戏那道题目

这里先手的选择，



### Solution 1:

````c++
class Solution {
public:
    bool canIWin(int max_choosable_integer, int desired_total) {
        // 以下两种情况可以直接得出结果，不用再进行计算
        if (max_choosable_integer >= desired_total) {
            return true; // 先手一定赢，选一次就可以赢
        } else if ((1 + max_choosable_integer) * max_choosable_integer / 2 < desired_total) {
            return false;
        }
        // 这里使用char 是为了方便状态转移中，构造缓存的 key
        vector<char> visited(max_choosable_integer + 1, '0'); // 标记数组
        unordered_map<string, bool> cache; // 缓存
        
        return CanIWin(visited, desired_total, cache);
    }
    
 private:
    bool CanIWin(vector<char>& visited, int desired_total,
                 unordered_map<string, bool>& cache) {
        string key = string(visited.begin(), visited.end()); // 构建一个 key
        if (cache.find(key) != cache.end()) {
            // 查询
            return cache.at(key);
        }
        
        const int len = visited.size();
        for (int i = 1; i < len; ++i) {
            if (visited[i] == '1') {
                continue;
            }
            
            visited[i] = 1 + '0'; // 做标记
            // 如果累加和达到要求或者对手输了
            if (desired_total - i <= 0 || !CanIWin(visited, desired_total - i, cache)) {
                cache[key] = true; // 缓存
                visited[i] = '0'; // 回溯
                return true;
            }
            visited[i] = '0'; // 回溯
        }
        
        cache[key] = false;
        return false;
    }
};
````

### Solution 2: 记忆化递归

这种解法的主流程其实还和上一种解法是一致的，

这种解法使用了位运算来优化，减少了构造 字符串 和查map 的的开销，这里是可以过的

```c++
class Solution {
public:
    bool canIWin(int max_choosable_integer, int desired_total) {
        // 以下两种情况可以直接得出结果，不用再进行计算
        if (max_choosable_integer >= desired_total) {
            return true; // 先手一定赢，选一次就可以赢
        } else if ((1 + max_choosable_integer) * max_choosable_integer / 2 < desired_total) {
            return false;
        }
        
        // 0 表示为初始化，1 表示赢，-1 表示输
        // dp 数组的每个表示状态的元素都是 max_choosable_integer 的二进制表示
        vector<int> dp((1 << max_choosable_integer) - 1, 0);
        
        return CanIWin(max_choosable_integer, desired_total, 0, dp) != 0;
    }
    
 private:
    int CanIWin(int max_choosable_integer, int desired_total, int state, vector<int>& dp) {
        if (dp[state] != 0) {
            // 如果已经有答案
            return dp[state];
        }
        
        for (int i = 1; i <= max_choosable_integer; ++i) {
            // 这里的 tmp 只有 1 位为 1，用于判断 state 上的指定位有没有使用过
            int tmp = (1 << (i - 1));
            if ((tmp & state) == 0) {
                // 如果没有使用过
                
                // 这里的递归隐含了回溯
                if (desired_total - i <= 0
                    || !CanIWin(max_choosable_integer, desired_total - i, tmp | state, dp)) {
                    dp[state] = 1;
                    return 1;
                }
            }
        }
        dp[state] = -1;
        return -1;
    }
};
```



