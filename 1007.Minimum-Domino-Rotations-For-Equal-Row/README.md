# [1007. Minimum Domino Rotations For Equal Row](https://leetcode.cn/problems/minimum-domino-rotations-for-equal-row/)

## 题目

In a row of dominoes, `tops[i]` and `bottoms[i]` represent the top and bottom halves of the `ith` domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the `ith` domino, so that `tops[i]` and `bottoms[i]` swap values.

Return the minimum number of rotations so that all the values in `tops` are the same, or all the values in `bottoms` are the same.

If it cannot be done, return `-1`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/14/domino.png)

```
Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
Output: 2
Explanation: 
The first figure represents the dominoes as given by tops and bottoms: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
```

**Example 2:**

```
Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
Output: -1
Explanation: 
In this case, it is not possible to rotate the dominoes to make one row of values equal.
```

 

**Constraints:**

- `2 <= tops.length <= 2 * 104`
- `bottoms.length == tops.length`
- `1 <= tops[i], bottoms[i] <= 6`

## 题目大意

在一排多米诺骨牌中，`A[i]` 和 `B[i]` 分别代表第 `i` 个多米诺骨牌的上半部分和下半部分。（一个多米诺是两个从 `1` 到 `6` 的数字同列平铺形成的 —— 该平铺的每一半上都有一个数字。）

我们可以旋转第 `i` 张多米诺，使得 `A[i]` 和 `B[i]` 的值交换

返回能使 `A` 中所有值或者 `B` 中所有值都相同的最小旋转次数

如果无法做到，返回 `-1`

### Solution 1: Greedy

这道题目可以参考 [这篇题解](https://leetcode.cn/problems/minimum-domino-rotations-for-equal-row/solution/1007-czhong-gui-zhong-ju-de-tan-xin-jie-7x6ea/)

这种解法其实就是尝试下列几种情况

- 全部变为 tops[0]，tops 和 bottoms 中取较小值
- 全部变为 bottoms[0]，tops 和bottoms 中去较小值

````c++
class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int top_ops = Process(tops[0], tops, bottoms);
        if (top_ops != -1 || tops[0] == bottoms[0]) {
            return top_ops;
        }
        return Process(bottoms[0], tops, bottoms);
    }
    
 private:
    int Process(int target, const vector<int> tops, const vector<int>& bottoms) {
        const int len = tops.size();
        
        int top_ops = 0, bottom_ops = 0;
        for (int i = 0; i < len; ++i) {
            if (tops[i] != target && bottoms[i] != target) {
                return -1;
            } else if (tops[i] != target) {
                // 交换
                ++top_ops;
            } else if (bottoms[i] != target) {
                // 交换
                ++bottom_ops;
            }
        }
        return min(bottom_ops, top_ops);
    }
};
````

