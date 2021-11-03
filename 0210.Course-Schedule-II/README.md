# [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)

## 题目

There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [ai, bi]` indicates that you **must** take course `bi` first if you want to take course `ai`.

- For example, the pair `[0, 1]`, indicates that to take course `0` you have to first take course `1`.

Return *the ordering of courses you should take to finish all courses*. If there are many valid answers, return **any** of them. If it is impossible to finish all courses, return **an empty array**.

 

**Example 1:**

```
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1].
```

**Example 2:**

```
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
```

**Example 3:**

```
Input: numCourses = 1, prerequisites = []
Output: [0]
```

 

**Constraints:**

- `1 <= numCourses <= 2000`
- `0 <= prerequisites.length <= numCourses * (numCourses - 1)`
- `prerequisites[i].length == 2`
- `0 <= ai, bi < numCourses`
- `ai != bi`
- All the pairs `[ai, bi]` are **distinct**.

## 题目大意

这里有 numCourse 门课程你可以选，从 0 到 numCourse - 1标号，给定一个 prerequisties其中 prerequisties[i] = [ai, bi] 表示在进行 课程 bi 之前，你必须进行完课程 ai，

* 例如，想要学习课程 `0` ，你需要先完成课程 `1` ，我们用一个匹配来表示：`[0,1]` 。

返回你上完这些课的所有顺序，如果有许多有效的答案，返回其中任意个，如果不可能进行完所有的答案，返回空

## 解题思路

这道题目是第 207 题的升级版，需要既使用 拓扑排序，也需要使用 DFS  来求的具体路径

### Solution 1:

 这种解法可以参考这篇题解：https://leetcode-cn.com/problems/course-schedule-ii/solution/tuo-bu-pai-xu-shen-du-you-xian-bian-li-python-dai-/

`````c++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // 建立入度数组
        vector<int> in_degrees(numCourses);
        for (const auto& prerequisite : prerequisites) {
            ++in_degrees[prerequisite[0]];
        }
        
        // 建立邻接表
        unordered_map<int, vector<int>> adj;
        for (int i = 0; i < numCourses; ++i) {
            vector<int> tmp;
            for (const auto& prerequisite : prerequisites) {
                if (prerequisite[1] == i) {
                    tmp.push_back(prerequisite[0]);
                }
            }
            adj.emplace(i, tmp);
        }
        
        // BFS
        queue<int> que;
        for (int i = 0; i < numCourses; ++i) {
            // 将 入度为 0 的节点入队
            if (in_degrees[i] == 0) {
                que.push(i);
            }
        }
        
        vector<int> res(numCourses);
        int count = 0;
        
        while (!que.empty()) {
          	// 出队
            int num = que.front();
            que.pop();
          	// 加入结果集中
            res[count] = num;
            ++count;
						// 遍历并更新邻接表
            const int len = adj.at(num).size();
            for (int i = 0; i < len; ++i) {
                --in_degrees[adj[num][i]];
              	// 将入度为 0 的节点加入队列中进行遍历
                if (in_degrees[adj.at(num)[i]] == 0) {
                    que.push(adj.at(num)[i]);
                }
            }
        }
        
        return count == numCourses ? res : vector<int>();
    }
};
`````

