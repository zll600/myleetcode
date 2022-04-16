# [841. Keys and Rooms](https://leetcode.com/problems/keys-and-rooms/)

## 题目

There are `n` rooms labeled from `0` to `n - 1` and all the rooms are locked except for room `0`. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of **distinct keys** in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

Given an array `rooms` where `rooms[i]` is the set of keys that you can obtain if you visited room `i`, return `true` *if you can visit **all** the rooms, or* `false` *otherwise*.

 

**Example 1:**

```
Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation: 
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.
```

**Example 2:**

```
Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.
```

 

**Constraints:**

- `n == rooms.length`
- `2 <= n <= 1000`
- `0 <= rooms[i].length <= 1000`
- `1 <= sum(rooms[i].length) <= 3000`
- `0 <= rooms[i][j] < n`
- All the values of `rooms[i]` are **unique**.

## 题目大意

给定 `n` 个房间，按照 `0` 到 `n - 1` 开始标号，除了 `0` 号房间之外的所有房间均以上锁，你的目标是参观所有的房间，然而，你不能进入上锁的房间，

当你进入房间中，你可以获得一些不同的钥匙，每个钥匙上有一个数字，表示其可以打开的房间号，你可以使用他们去打开其他房间，

给定一个数组 `rooms`，其中 `rooms[i]` 表示你可以从每个房间获得的钥匙集合，

如果你可以参观所有的房间，返回 `true`


### Solution 1: DFS

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0841.Keys-and-Rooms/)

````c++
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        unordered_set<int> visited;
        visited.insert(0);
        DFS(rooms, 0, visited);
        
        return visited.size() == rooms.size();
    }
    
 private:
    void DFS(const vector<vector<int>>& rooms, int key,
            unordered_set<int>& visited) {
        // 遍历这个key 可以进入的房间中的钥匙可以打开的所有的房间
        // cout << key << endl;
        for (int num : rooms[key]) {
            if (visited.find(num) != visited.end()) {
                continue;
            }
            visited.insert(num);
            DFS(rooms, num, visited);
        }
    }
};
````
