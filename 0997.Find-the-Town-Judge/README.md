# [997. Find the Town Judge](https://leetcode.com/problems/find-the-town-judge/)

## 题目

In a town, there are `n` people labeled from `1` to `n`. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

1. The town judge trusts nobody.
2. Everybody (except for the town judge) trusts the town judge.
3. There is exactly one person that satisfies properties **1** and **2**.

You are given an array `trust` where `trust[i] = [ai, bi]` representing that the person labeled `ai` trusts the person labeled `bi`.

Return *the label of the town judge if the town judge exists and can be identified, or return* `-1` *otherwise*.

 

**Example 1:**

```
Input: n = 2, trust = [[1,2]]
Output: 2
```

**Example 2:**

```
Input: n = 3, trust = [[1,3],[2,3]]
Output: 3
```

**Example 3:**

```
Input: n = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1
```

 

**Constraints:**

- `1 <= n <= 1000`
- `0 <= trust.length <= 104`
- `trust[i].length == 2`
- All the pairs of `trust` are **unique**.
- `ai != bi`
- `1 <= ai, bi <= n`

## 题目大意

在一个城镇中，有  `n` 个人标记为从 `1` 到 `n`，这里有一个人是小镇的秘密法官

如果这个个法官存在：

1. 这个法官不相信任何人
2. 每个人（除了法官自己）相信法官
3. 有且只有一个人同时满足条件 **1** 和 **2**

给定一个数组 `trust` 其中 `trust[i] = [ai, bi]` 表示标签 `ai` 的人，相信标签 `bi` 的人，

如果法官存在而且可以被确认，则返回他的标签，否则返回 `-1`，

## 解题思路

对于这道题目而言，我们就是要找到一个人

- 有 n - 1 个人相信自己
- 自己不相信任何人

### Solution 1:

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0997.Find-the-Town-Judge/)

````c++
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trusts) {
        // 这里先处理一下边界情况
        if (n == 1 && trusts.size() == 0) {
            return 1;
        }

        const int len = trusts.size();
        // 设置一个入度集合，表示 有多少人相信这个人
        unordered_map<int, int> judges;
        for (const auto& trust : trusts) {
            ++judges[trust[1]];
        }

        // 在入度集合中删除相信别人的人，即出度不为 0 的人
        for (const auto& trust : trusts) {
            if (judges.find(trust[0]) != judges.end()) {
                judges.erase(trust[0]);
            }
        }

        // 遍历剩下的人，找到 入度为 n - 1 的人
        for (const auto& judge : judges) {
            if (judge.second == n- 1) {
                return judge.first;
            }
        }

        return -1;
    }
};
````

