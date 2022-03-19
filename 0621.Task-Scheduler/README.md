# [621. Task Scheduler](https://leetcode-cn.com/problems/task-scheduler/)

## 题目

Given a characters array `tasks`, representing the tasks a CPU needs to do, where each letter represents a different task. Tasks could be done in any order. Each task is done in  one unit of time. For each unit of time, the CPU could complete either  one task or just be idle.

However, there is a non-negative integer `n` that represents the cooldown period between two **same tasks** (the same letter in the array), that is that there must be at least `n` units of time between any two same tasks.

Return *the least number of units of times that the CPU will take to finish all the given tasks*.

 

**Example 1:**

```
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: 
A -> B -> idle -> A -> B -> idle -> A -> B
There is at least 2 units of time between any two same tasks.
```

**Example 2:**

```
Input: tasks = ["A","A","A","B","B","B"], n = 0
Output: 6
Explanation: On this case any permutation of size 6 would work since n = 0.
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
And so on.
```

**Example 3:**

```
Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
Output: 16
Explanation: 
One possible solution is
A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle -> idle -> A
```

 

**Constraints:**

- `1 <= task.length <= 104`
- `tasks[i]` is upper-case English letter.
- The integer `n` is in the range `[0, 100]`.

## 题目大意

给定一个字符数组 `task`，表示 `cpu` 需要执行，*不同的字符* 表示 *不同的任务* ，任务可以按照 *任意顺序* 被执行，

并且每个任务都可以在 `1` 个单位时间内执行完。在任何一个单位时间，`CPU` 可以完成一个任务，或者处于待命状态

然而，两个 *相同种类* 的任务之间必须有长度为整数 `n` 的冷却时间，因此至少有连续 `n` 个单位时间内 `CPU` 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的 *最短时间*最短时间 。

## 解题思路

这道题目可以参考 [这篇题解](https://leetcode-cn.com/problems/task-scheduler/solution/tong-si-xiang-jian-ji-gao-xiao-by-hzhu212/) 

和 [这篇题解](https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/)

设计 大小为 `n + 1` 的桶，同一种任务只能放在相邻的桶中，不同的任务可以放在同一个桶中，那么需要的桶的数目就是 `数量最多的任务的数量 - 1`，

如果最后一个桶中最终有 x 个任务，那么就需要再加上 桶中剩余任务数目，

如果任务的重复次数较低，那么最终消耗的时间就是所有任务的数量之和了


### Solution 1:


````c++
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // 我们先统计频数
        vector<int> freq(26);
        for (char task : tasks) {
            ++freq[task - 'A'];
        }

        // 这里按照每个任务的数目进行排序
        sort(freq.begin(), freq.end(), [](int a, int b) {
            return a > b;
        });

        // 找出人物数目最大值的个数
        int cnt = 1;
        while (cnt < 26 && freq[cnt] == freq[0]) {
            ++cnt;
        }

        // 返回最大值和
        return max(static_cast<int>(tasks.size()), cnt + (n + 1) * (freq[0] - 1));
    }
};
````
