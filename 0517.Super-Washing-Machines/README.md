# [517. Super Washing Machines](https://leetcode-cn.com/problems/super-washing-machines/)

You have `n` super washing machines on a line. Initially, each washing machine has some dresses or is empty.

For each move, you could choose any `m` (`1 <= m <= n`) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time.

Given an integer array `machines` representing the number of dresses in each washing machine from left to right on the line, return *the minimum number of moves to make all the washing machines have the same number of dresses*. If it is not possible to do it, return `-1`.

 

**Example 1:**

```
Input: machines = [1,0,5]
Output: 3
Explanation:
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3
3rd move:    2     1 <-- 3    =>    2     2     2
```

**Example 2:**

```
Input: machines = [0,3,0]
Output: 2
Explanation:
1st move:    0 <-- 3     0    =>    1     2     0
2nd move:    1     2 --> 0    =>    1     1     1
```

**Example 3:**

```
Input: machines = [0,2,0]
Output: -1
Explanation:
It's impossible to make all three washing machines have the same number of dresses.
```

 

**Constraints:**

- `n == machines.length`
- `1 <= n <= 104`
- `0 <= machines[i] <= 105`

## 题目大意

有 `n` 台超级洗衣机放在同一条直线上，每台洗衣机可能有一些衣服，也可能是空的，

每一次，你可以选择 `m`(1 <= m <= n) 台洗衣机，将每台洗衣机中的意见衣服送到相邻的洗衣机中,

给定一个数组 machines 从左至右表示每台洗衣机中衣物的数量，返回使得所有洗衣机中剩下的衣物数量相等的最少操作步数，如果不能，返回 -1


## 解题思路


### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/super-washing-machines/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-mzqia/)

````c++
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        const int len = machines.size();
        const int sum = accumulate(machines.begin(), machines.end(), 0);
        // 如果最终每台洗衣机中的衣服不可能相同，则直接返回
        if (sum % len != 0) {
            return -1;
        }
        
        int target = sum / len; // 最终每台洗衣机中的衣服数目
        // 维护每个位置左边和右边衣服的总数
        int lhs = 0, rhs = sum;
        int res = 0; // 最终的结果
        for (int i = 0; i < len; ++i) {
            rhs -= machines[i];
            
            // 从右边到左边 即为 左边的最终状态和左边现在状态的差值
            // 如果结果为负，表示不应该从右边到左边
            const int right_to_left = max(i * target - lhs, 0);
            // 从左边到右边，即为 右边的最终状态和右边现在状态的差值
            // 如果结果为负，表示不该从左边到右边
            const int left_to_right = max((len - i - 1) * target - rhs, 0);
            // 取最大值才能使的每个位置都可以符合条件
            res = max(res, right_to_left + left_to_right);
            
            lhs += machines[i];
        }
        
        return res;
    }
};
````
