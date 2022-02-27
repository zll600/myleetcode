# [502. IPO](https://leetcode-cn.com/problems/ipo/)

## 题目

Suppose LeetCode will start its **IPO** soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the **IPO**. Since it has limited resources, it can only finish at most `k` distinct projects before the **IPO**. Help LeetCode design the best way to maximize its total capital after finishing at most `k` distinct projects.

You are given `n` projects where the `ith` project has a pure profit `profits[i]` and a minimum capital of `capital[i]` is needed to start it.

Initially, you have `w` capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

Pick a list of **at most** `k` distinct projects from given projects to **maximize your final capital**, and return *the final maximized capital*.

The answer is guaranteed to fit in a 32-bit signed integer.

 

**Example 1:**

```
Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4
Explanation: Since your initial capital is 0, you can only start the project indexed 0.
After finishing it you will obtain profit 1 and your capital becomes 1.
With capital 1, you can either start the project indexed 1 or the project indexed 2.
Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
```

**Example 2:**

```
Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
Output: 6
```

 

**Constraints:**

- `1 <= k <= 105`
- `0 <= w <= 109`
- `n == profits.length`
- `n == capital.length`
- `1 <= n <= 105`
- `0 <= profits[i] <= 104`
- `0 <= capital[i] <= 109`

## 题目大意

假设 **力扣（LeetCode）** 即将开始 `IPO` 。为了以更高的价格将股票卖给风险投资公司，力扣 希望在 `IPO` 之前开展一些项目以增加其资本。 由于资源有限，它只能在 `IPO` 之前完成最多 `k` 个不同的项目。帮助 力扣 设计完成最多 `k` 个不同项目后得到最大总资本的方式。

给你 `n` 个项目。对于每个项目 `i` ，它都有一个纯利润 `profits[i]` ，和启动该项目需要的最小资本 `capital[i]` 。

最初，你的资本为 `w` 。当你完成一个项目时，你将获得纯利润，且利润将被添加到你的总资本中。

总而言之，从给定项目中选择 最多 `k` 个不同项目的列表，以 **最大化最终资本** ，并输出最终可获得的最多资本。

答案保证在 32 位有符号整数范围内。

## 解题思路

这道题目需要解决的问题就是

- 每次在自己有限的资本前提下，每次选择可以选择的项目中利润最大的，
- 解决如果取最大的问题

这道题目一开始的做法是根据已知的数据生成一个 需要的资本---纯利润之间 的二元组，然后将按照 需要资本的升序排序，然后需要资本相同的项目按照纯利润的降序排序，但是之后发现必须要在左右可以选择的项目中，选择利润最大的，而不是在某一组需要资本相同的项目之间，因为这道题目，项目需要的资本和纯利润没有必然的关系，所以这里其实对 纯利润的排序，后面依旧用不上，

- 这里应该使用大顶堆来选取利润最大的

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/ipo/solution/gong-shui-san-xie-noxiang-xin-ke-xue-xi-fk1ra/)

````c++
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        const int len = profits.size();
        // 先生成一个二元组，
        vector<vector<int>> data(len, vector<int>(2, 0));
        for (int i = 0; i < len; ++i) {
            data[i][0] = capital[i];
            data[i][1] = profits[i];
        }

        // 按照 所需资本的升序排序
        sort(data.begin(), data.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            return lhs[0] != rhs[0] ? lhs[0] < rhs[0] : lhs[1] > rhs[1];
        });

        priority_queue<int> que;
        int idx = 0;
        for (int i = 0; i < k; ++i) {
            while (idx < len && data[idx][0] <= w) {
                // 将可以完成的项目全部加入堆中
                que.push(data[idx][1]);
                ++idx;
            }
            if (que.empty()) {
                // 如果栈空，则直接结束
                break;
            }

            // 取最大值
            w += que.top();
            que.pop();
        }

        return w;
    }
};
````
