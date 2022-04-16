# [826. Most Profit Assigning Work](https://leetcode.com/problems/most-profit-assigning-work/)

## 题目

You have `n` jobs and `m` workers. You are given three arrays: `difficulty`, `profit`, and `worker` where:

- `difficulty[i]` and `profit[i]` are the difficulty and the profit of the `ith` job, and
- `worker[j]` is the ability of `jth` worker (i.e., the `jth` worker can only complete a job with difficulty at most `worker[j]`).

Every worker can be assigned **at most one job**, but one job can be **completed multiple times**.

- For example, if three workers attempt the same job that pays `$1`, then the total profit will be `$3`. If a worker cannot complete any job, their profit is `$0`.

Return the maximum profit we can achieve after assigning the workers to the jobs.

 

**Example 1:**

```
Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get a profit of [20,20,30,30] separately.
```

**Example 2:**

```
Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
Output: 0
```

 

**Constraints:**

- `n == difficulty.length`
- `n == profit.length`
- `m == worker.length`
- `1 <= n, m <= 104`
- `1 <= difficulty[i], profit[i], worker[i] <= 105`

## 题目大意

有 `n` 个 jobs 和 `m` 个 workers，给定三个数组：`difficulty`,`profit`, 和 `worker` 其中

- `difficulty[i]` 和 `profit[i]` 是第 `i` 个job 的难度和收益
- `worker[j]` 是这个工人的能力（工人最多完成难度为 `worker[j]` 的job）

每个worker 最多分配一个 job,但是每个job 可以被完成多次，

- 例如：如果是三个 workers 完成同样收益为 1 的job，总收入是 3，如果一个woker 不能完成任意job，总收入为 0,

返回分配job 给 workers 之后能获得的最大利润

## 解题思路

这道题目的难点在于按照 difficuity 或者 profit 单独来排序都是不可行的，是无法做到降低时间复杂度的，所以难点在于要同时兼顾二者才可以

### Solution 1: Sliding Window

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0826.Most-Profit-Assigning-Work/)

这里我们将 worker按照能力升序排序，job 先按照难度升序排序，然后 tasks 更新到 i 位置为止所有能获得的最大收益，

````c++
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        const int len = profit.size();
        
        // 对 worker 做一个排序
        sort(worker.begin(), worker.end());
        vector<pair<int, int>> tasks;
        for (int i = 0; i < len; ++i) {
            tasks.emplace_back(difficulty[i], profit[i]);
        }
        // 将tasks 先按照难度的升序排序
        sort(tasks.begin(), tasks.end());
        // 每个位置，表示当前所能达到的最大收益，通过不断的比较来达到目的
        for (int i = 1; i < len; ++i) {
            tasks[i].second = max(tasks[i].second, tasks[i - 1].second);
        }
        
        int idx = 0;
        int res = 0;
        // 遍历素有的 worker 分配job
        for (int work : worker) {
            if (idx < len && work >= tasks[idx].first) {
                ++idx;
            }
            if (idx > 0) {
                res += tasks[idx].second;
            }
        }
        
        return res;
    }
};
````
