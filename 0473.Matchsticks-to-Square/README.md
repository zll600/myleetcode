# [473. Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/)

## 题目

You are given an integer array `matchsticks` where `matchsticks[i]` is the length of the `ith` matchstick. You want to use **all the matchsticks** to make one square. You **should not break** any stick, but you can link them up, and each matchstick must be used **exactly one time**.

Return `true` if you can make this square and `false` otherwise.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/04/09/matchsticks1-grid.jpg)

```
Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
```

**Example 2:**

```
Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.
```

 

**Constraints:**

- `1 <= matchsticks.length <= 15`
- `1 <= matchsticks[i] <= 108`

## 题目大意

给定一个数组，数组的每一项 `matchstick[i]` 表示第 i 根火柴的长度，你想利用所有的火柴制造一个正方形，你必须使用所有的火柴，且每个火柴只使用一次，返回是否可以拼成一个正方形，

## 解题思路

这道题目其实就是组合的题目，用到的就是回溯法

这道题目有两种思路，可以参考这篇题解：https://leetcode-cn.com/problems/matchsticks-to-square/solution/hui-su-dfszuo-xuan-ze-by-xing-ba-m-c2dm/

* 选择火柴，将火柴划入到不同的边中，这种解法，不减枝是过不了的
* 选择边，一条一条去凑边，这种解法需要添加一个 visit 数组来记录已经使用过的边

### Solution 1:

这种解法对火柴进行 DFS，将火柴分入不同的边中

```c++
class Solution {
public:
    bool makesquare(vector<int>& matchsticks) {
        const int len = matchsticks.size();
        if (len < 4) {
            return false; // 不足四条边
        }
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4 != 0) {
            return false; // 长度不是 4 的倍数
        }
        // 这里做一个优化，从大的开始遍历
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        
        vector<int> sides(4);
        return DFS(matchsticks, 0, sum >> 2, sides);
    }
    
  private:
    bool DFS(vector<int>& matchsticks, int idx, int target, vector<int>& sides) {
        if (idx == matchsticks.size()) {
            // 使用所有的火柴
            if (sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3]) {
                // 并且所有的边长都是符合条件的
                return true;
            }
            return false;
        }
        
        for (int i = 0; i < 4; ++i) {
            if (sides[i] + matchsticks[idx] > target || (i > 0 && sides[i] == sides[i - 1])) {
                // 这里做一个剪枝
                // 如果当前边的长度，已经大于要求的
                // 或者如果当前边的长度已经等于上一个边的长度，说明两条边都已经满足条件了
                continue;
            }
            
            sides[i] += matchsticks[idx]; // 更新
            if (DFS(matchsticks, idx + 1, target, sides)) {
                // 递归验证
                return true;
            }
            sides[i] -= matchsticks[idx]; // 撤销
        }
        
        return false;
    }    
};
```

