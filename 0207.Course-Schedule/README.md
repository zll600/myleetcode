# [207. Course Schedule](https://leetcode.com/problems/course-schedule/) 

## 题目

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first if you want to take course `ai`.

- For example, the pair `[0, 1]`, indicates that to take course `0` you have to first take course `1`.

Return `true` if you can finish all courses. Otherwise, return `false`.

 

**Example 1:**

```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
```

**Example 2:**

```
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
```

 

**Constraints:**

- `1 <= numCourses <= 105`
- `0 <= prerequisites.length <= 5000`
- `prerequisites[i].length == 2`
- `0 <= ai, bi < numCourses`
- All the pairs prerequisites[i] are **unique**.

## 题目大意

你总计有 numCourse 的课程要选，从 0 到 numCourse - 1，给定一个数组 prerequisites 其中 prerequisies[i] = [ai, bi] 表示你在修 bi 表示的课程前必须先修完 ai 表示的课程

- 例如，先修课程对 `[0, 1]` 表示：想要学习课程 `0` ，你需要先完成课程 `1` 。

如果能完成所有的课，返回 true，否则返回 false，

## 解题思路

这道题目是一道典型的拓扑排序的题目，很

### Solution 1: BFS + Greedy

这种解法可以参考这篇题解:https://leetcode-cn.com/problems/course-schedule/solution/tuo-bu-pai-xu-by-liweiwei1419/

````c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.empty()) {
            return true;
        }
        
        // 入度数组
        vector<int> in_degrees(numCourses);
        for (const auto& pre : prerequisites) {
            ++in_degrees[pre[0]];
        }
        
        // 邻接矩阵
        unordered_map<int, vector<int>> adj;
        for (int i = 0; i < numCourses; ++i) {
            vector<int> tmp;
            for (const auto& pre : prerequisites) {
                if (pre[1] == i) {
                    tmp.push_back(pre[0]);
                }
            }
            adj.emplace(i, tmp);
        }
        
        // 将入度为 0 的节点入队
        queue<int> que;
        for (int i = 0; i < numCourses; ++i) {
            if (in_degrees[i] == 0) {
                que.push(i);
            }
        }
        
        vector<int> res;
        // 开始广度优先搜索
        while (!que.empty()) {
            int num = que.front();
            que.pop();
            
            res.push_back(num);
            const int len = adj.at(num).size();
            for (int i = 0; i < len; ++i) {
                // 更新入队数组，
                --in_degrees[adj.at(num)[i]];
                // 将入度为 0 的节点入队
                if (in_degrees[adj.at(num)[i]] == 0) {
                    que.push(adj.at(num)[i]);
                }
            }
        }
        
        return res.size() == numCourses;
    }
};
````

### Solution 2: DFS

这个留待以后实现

