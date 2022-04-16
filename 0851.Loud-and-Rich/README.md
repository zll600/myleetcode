# [851. Loud and Rich](https://leetcode.com/problems/loud-and-rich/)

## 题目

There is a group of `n` people labeled from `0` to `n - 1` where each person has a different amount of money and a different level of quietness.

You are given an array `richer` where `richer[i] = [ai, bi]` indicates that `ai` has more money than `bi` and an integer array `quiet` where `quiet[i]` is the quietness of the `ith` person. All the given data in richer are **logically correct** (i.e., the data will not lead you to a situation where `x` is richer than `y` and `y` is richer than `x` at the same time).

Return *an integer array* `answer` *where* `answer[x] = y` *if* `y` *is the least quiet person (that is, the person* `y` *with the smallest value of* `quiet[y]`*) among all people who definitely have equal to or more money than the person* `x`.

 

**Example 1:**

```
Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet = [3,2,5,4,6,1,7,0]
Output: [5,5,2,5,4,5,6,7]
Explanation: 
answer[0] = 5.
Person 5 has more money than 3, which has more money than 1, which has more money than 0.
The only person who is quieter (has lower quiet[x]) is person 7, but it is not clear if they have more money than person 0.
answer[7] = 7.
Among all people that definitely have equal to or more money than person 7 (which could be persons 3, 4, 5, 6, or 7), the person who is the quietest (has lower quiet[x]) is person 7.
The other answers can be filled out with similar reasoning.
```

**Example 2:**

```
Input: richer = [], quiet = [0]
Output: [0]
```

 

**Constraints:**

- `n == quiet.length`
- `1 <= n <= 500`
- `0 <= quiet[i] < n`
- All the values of `quiet` are **unique**.
- `0 <= richer.length <= n * (n - 1) / 2`
- `0 <= ai, bi < n`
- `ai != bi`
- All the pairs of `richer` are **unique**.
- The observations in `richer` are all logically consistent.

## 题目大意

有一组 `n` 个人作为实验对象，从 `0` 到 `n - 1` 编号，其中每个人都有不同数目的钱，以及不同程度的安静值 `（quietness）`。为了方便起见，我们将编号为 `x` 的人简称为 `"person x "`。

给你一个数组 `richer` ，其中 `richer[i] = [ai, bi]` 表示 `person ai` 比 `person bi` 更有钱。另给你一个整数数组 `quiet` ，其中 `quiet[i]` 是 `person i` 的安静值。

`richer` 中所给出的数据 逻辑自洽（也就是说，在 `person x` 比 `person y` 更有钱的同时，不会出现 `person y` 比 `person x` 更有钱的情况 ）。

现在，返回一个整数数组 `answer` 作为答案，其中 `answer[x] = y` 的前提是，在所有拥有的钱肯定不少于 `person x` 的人中，`person y` 是最安静的人（也就是安静值 `quiet[y]` 最小的人）。


## 解题思路


### Solution 1: Topo Sort

这道题目可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0851.Loud-and-Rich/)

若 ai 比 bi 富有，则我们表示为 ai 指向 bi 的一条边，通过 richer 数组，我们可以得到一个有向无环图（穷的不可能比富的富），我们只能从指向 bi 的ai 中（或者其自身）选择 quiet 值最小的，

````c++
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richers, vector<int>& quiet) {
        const int len = quiet.size();
        // 建图
        // 邻接表
        unordered_map<int, vector<int>> edges(len);
        // 入度数组
        vector<int> indegrees(len, 0);
        for (const auto& richer : richers) {
            int rich = richer[0], poor = richer[1];
            edges[rich].push_back(poor);
            ++indegrees[poor];
        }

        // 初始化结果数组
        vector<int> res(len, 0);
        for (int i = 0; i < len; ++i) {
            res[i] = i;
        }

        queue<int> que;
        // 将入度为 0 的点入队，即没有比自身更富有的人了
        for (int i = 0; i < len; ++i) {
            if (indegrees[i] == 0) {
                que.push(i);
            }
        }

        while (!que.empty()) {
            const int que_len = que.size();
            for (int i = 0; i < len; ++i) {
                int cur = que.front();
                que.pop();

                for (int dst : edges[cur]) {
                    --indegrees[dst];

                    // 如果比自己富有的人的 y 的quiet 比自己还小，就更新
                    if (quiet[res[dst]] > quiet[res[cur]]) {
                        res[dst] = res[cur];
                    }

                    if (indegrees[dst] == 0) {
                        que.push(dst);
                    }
                }
            }
        }

        return res;
    }
};
````
