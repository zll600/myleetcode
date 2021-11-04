# [752. Open the Lock](https://leetcode.com/problems/open-the-lock/)

## 题目

You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: `'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'`. The wheels can rotate freely and wrap around: for example we can turn `'9'` to be `'0'`, or `'0'` to be `'9'`. Each move consists of turning one wheel one slot.

The lock initially starts at `'0000'`, a string representing the state of the 4 wheels.

You are given a list of `deadends` dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a `target` representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

 

**Example 1:**

```
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation:
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".
```

**Example 2:**

```
Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation:
We can turn the last wheel in reverse to move from "0000" -> "0009".
```

**Example 3:**

```
Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation:
We can't reach the target without getting stuck.
```

**Example 4:**

```
Input: deadends = ["0000"], target = "8888"
Output: -1
```

 

**Constraints:**

- `1 <= deadends.length <= 500`
- `deadends[i].length == 4`
- `target.length == 4`
- target **will not be** in the list `deadends`.
- `target` and `deadends[i]` consist of digits only.

## 题目大意

你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： ‘0’, ‘1’, ‘2’, ‘3’, ‘4’, ‘5’, ‘6’, ‘7’, ‘8’, ‘9’ 。每个拨轮可以自由旋转：例如把 ‘9’ 变为 ‘0’，‘0’ 变为 ‘9’ 。每次旋转都只能旋转一个拨轮的一位数字。锁的初始数字为 ‘0000’ ，一个代表四个拨轮的数字的字符串。列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。字符串 target 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1 

## 解题思路:

这道题目可以联系第 126 题、第 127 题，都可以利用 BFS 来解决，联系这几道题目，可以熟悉一下双向 BFS 的使用

### Solution1:

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/open-the-lock/solution/gong-shui-san-xie-yi-ti-shuang-jie-shuan-wyr9/

不过注意在状态转移时两种语言还是有区别的。

````c++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        string src = "0000";  // 初始状态
        if (src == target) {  // 边界情况 
            return 0;
        }
        
        // 将死锁条件加入到集合中，如果出现直接返回失败
        unordered_set<string> dead_set(deadends.begin(), deadends.end());
        if (dead_set.find(target) != dead_set.end()
            || dead_set.find(src) != dead_set.end()) {
            return -1;
        }
        
        return BFS(src, target, dead_set);
    }
    
 private:
    // 双向
    int BFS(const string& src, const string& target,
        const unordered_set<string>& dead_set) {
        // 两个队列
        queue<string> que1, que2;
        que1.push(src);
        que2.push(target);
        // 这两个 map 可以代替 visited 数组
        unordered_map<string, int> record1, record2;
        record1.emplace(src, 0);
        record2.emplace(target, 0);
        
        // 如果两个都不为空，继续搜索
        while (!que1.empty() && !que2.empty()) {
            int res = -1;
            // 选择较小的一个进行搜索
            if (que1.size() <= que2.size()) {
                res = Update(que1, record1, record2, dead_set);
            } else {
                res = Update(que2, record2, record1, dead_set);
            }
            
            if (res != -1) {
                return res;
            }
        }
        
        return -1;
    }
    
    // 搜索
    int Update(queue<string>& que, unordered_map<string, int>& cur,
              const unordered_map<string, int>& other,
              const unordered_set<string>& dead_set) {
        string str = que.front();
        que.pop();
        int steps = cur.at(str);
        
        for (int i = 0; i < 4; ++i) {
            int origin = str[i] - '0';  // 改变
            for (int j = -1; j < 2; j += 2) {
                int next = (origin + j) % 10;
                if (next == -1) {
                    next = 9;
                }
                
                str[i] = next + '0';
                
                // 如果这个节点已经到达过了，跳过
                if (dead_set.find(str) != dead_set.end()
                    || cur.find(str) != cur.end()) {
                    continue;
                }
                // 如果找到，直接返回
                if (other.find(str) != other.end()) {
                    return steps + 1 + other.at(str);
                } else {
                    // 否则加入队列中继续查找
                    que.push(str);
                    cur.emplace(str, steps + 1);
                }
            }
            str[i] = origin + '0';  // 恢复
        }
        
        return -1;
    }
};
````

