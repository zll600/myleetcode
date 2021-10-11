# [365. Water and Jug Problem](https://leetcode.com/problems/water-and-jug-problem/)

## 题目

You are given two jugs with capacities `jug1Capacity` and `jug2Capacity` liters. There is an infinite amount of water supply available. Determine whether it is possible to measure exactly `targetCapacity` liters using these two jugs.

If `targetCapacity` liters of water are measurable, you must have `targetCapacity` liters of water contained **within one or both buckets** by the end.

Operations allowed:

- Fill any of the jugs with water.
- Empty any of the jugs.
- Pour water from one jug into another till the other jug is completely full, or the first jug itself is empty.

 

**Example 1:**

```
Input: jug1Capacity = 3, jug2Capacity = 5, targetCapacity = 4
Output: true
Explanation: The famous Die Hard example 
```

**Example 2:**

```
Input: jug1Capacity = 2, jug2Capacity = 6, targetCapacity = 5
Output: false
```

**Example 3:**

```
Input: jug1Capacity = 1, jug2Capacity = 2, targetCapacity = 3
Output: true
```

 

**Constraints:**

- `1 <= jug1Capacity, jug2Capacity, targetCapacity <= 106`

## 题目大意

给定两个容量分别为 jug1Capacity 和 jug2Capacity 升的水壶，这里有无限多的水，决定能否通过这两个水壶得到准确的 targetCapacity 升水

如果可以，最后请用以上水壶中的一或两个来盛放取得的 *z升* 水。

下面时你允许的选项：

* 装满任意一个水壶
* 清空任意一个水壶
* 从一个水壶向另外一个水壶倒水，直到装满或者倒空

## 解题思路

这类问题，一般多要用到搜索算法，这道题目适合用广度优先搜索，如果有深度优先搜索，可能会超时

### 解法1（广搜）

这道题目有一个需要注意的点，以 pair 做键的时候，需要自定义哈希函数，否则会编译报错

**状态定义**：这道题目的状态涉及到了两个变量，A 中当前的水量，和 B 中当前的水量，

**状态转移**：这道题状态转移有三种操作，可以产生不同的 8 种状态，直到一个状态满足题意即可

`````c++
class Solution {
public:
    struct pair_hash {
        template <class T1, class T2>
        size_t operator () (pair<T1, T2> const &pair) const {
            size_t h1 = hash<T1>()(pair.first); //用默认的 hash 处理 pair 中的第一个数据 X1
            size_t h2 = hash<T2>()(pair.second);//用默认的 hash 处理 pair 中的第二个数据 X2
            return h1 ^ h2;
        }
    };
    
    using State = pair<int, int>;
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        if (jug1Capacity + jug2Capacity < targetCapacity) {  // 处理边界情况，剪枝
            return false;
        }
        
        State init(0, 0);
        queue<State> que;
        unordered_set<State, pair_hash> visited;
        
        que.push(init);
        visited.insert(init);
        
        while (!que.empty()) {
            State head = que.front();
            que.pop();
            
            int cur_x = head.first;
            int cur_y = head.second;
            
            // 终止条件
            if (cur_x == targetCapacity || cur_y == targetCapacity || cur_x + cur_y == targetCapacity) {
                return true;
            }
            
            // 获得下一步的状态
            vector<State> next_states = GetNextStates(cur_x, cur_y, jug1Capacity, jug2Capacity);
            
            for (const State& state : next_states) {
                if (visited.find(state) == visited.end()) {
                    que.push(state);
                    // 添加到队列之后，必须马上记录已经访问过了，否则会出现死循环
                    visited.insert(state);
                }
            }
        }
        return false;
    }
    
 private:
    vector<State> GetNextStates(int cur_x, int cur_y, int x, int y) {
        // 这里先判断能否发生转移，然后才添加状态
        vector<State> next_states;
        
        // 没有满的时候，才可以加水加满
        if (cur_x < x) {
            next_states.emplace_back(x, cur_y);
        }
        if (cur_y < y) {
            next_states.emplace_back(cur_x, y);
        }
        
        // 不为空的时候才可以，倒掉置空
        if (cur_x > 0) {
            next_states.emplace_back(0, cur_y);
        }
        if (cur_y > 0) {
            next_states.emplace_back(cur_x, 0);
        }
        
        // 将 A 导入 B
        // B 可以满
        if (cur_x - (y - cur_y) > 0) {
            next_states.emplace_back(cur_x - (y - cur_y), y);
        }
        // B 未满
        if (cur_x + cur_y < y) {
            next_states.emplace_back(0, cur_y + cur_x);
        }
        
        // 将 B 倒入 A
        // A 可以满
        if (cur_y - (x - cur_x) > 0) {
            next_states.emplace_back(x, y - (x - cur_x));
        }
        // A 未满
        if (cur_x + cur_y < x) {
            next_states.emplace_back(cur_x + cur_y, 0);
        }
        
        return next_states;
    }
};
`````

### 解法2

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/water-and-jug-problem/solution/hu-dan-long-wei-liang-zhang-you-yi-si-de-tu-by-ant/

