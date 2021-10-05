# [1583. Count Unhappy Friends](https://leetcode.com/problems/count-unhappy-friends/)

## 题目

You are given a list of `preferences` for `n` friends, where `n` is always **even**.

For each person `i`, `preferences[i]` contains a list of friends **sorted** in the **order of preference**. In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from `0` to `n-1`.

All the friends are divided into pairs. The pairings are given in a list `pairs`, where `pairs[i] = [xi, yi]` denotes `xi` is paired with `yi` and `yi` is paired with `xi`.

However, this pairing may cause some of the friends to be unhappy. A friend `x` is unhappy if `x` is paired with `y` and there exists a friend `u` who is paired with `v` but:

- `x` prefers `u` over `y`, and
- `u` prefers `x` over `v`.

Return *the number of unhappy friends*.

 

**Example 1:**

```
Input: n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
Output: 2
Explanation:
Friend 1 is unhappy because:
- 1 is paired with 0 but prefers 3 over 0, and
- 3 prefers 1 over 2.
Friend 3 is unhappy because:
- 3 is paired with 2 but prefers 1 over 2, and
- 1 prefers 3 over 0.
Friends 0 and 2 are happy.
```

**Example 2:**

```
Input: n = 2, preferences = [[1], [0]], pairs = [[1, 0]]
Output: 0
Explanation: Both friends 0 and 1 are happy.
```

**Example 3:**

```
Input: n = 4, preferences = [[1, 3, 2], [2, 3, 0], [1, 3, 0], [0, 2, 1]], pairs = [[1, 3], [0, 2]]
Output: 4
```

 

**Constraints:**

- `2 <= n <= 500`
- `n` is even.
- `preferences.length == n`
- `preferences[i].length == n - 1`
- `0 <= preferences[i][j] <= n - 1`
- `preferences[i]` does not contain `i`.
- All values in `preferences[i]` are unique.
- `pairs.length == n/2`
- `pairs[i].length == 2`
- `xi != yi`
- `0 <= xi, yi <= n - 1`
- Each person is contained in **exactly one** pair.

## 题目大意

给定一个 n 位朋友的亲近列表，其中 n 总为偶数，

对每位朋友 i，preferences[i] 包含一份 按亲近程度从高到低排列 的朋友列表。换句话说，排在列表前面的朋友与 i 的亲近程度比排在列表后面的朋友更高。每个列表中的朋友均以 0 到 n-1 之间的整数表示

所有的朋友被分成几对，配对情况以列表 `pairs` 给出，其中 `pairs[i] = [xi, yi]` 表示 `xi` 与 `yi` 配对，且 `yi` 与 `xi` 配对。

但是，这样的配对情况可能会使其中部分朋友感到不开心。在 x 与 y 配对且 u 与 v 配对的情况下，如果同时满足下述两个条件，x 就会不开心：

* x 与 u 的亲近程度胜过 x 与 y，且
* u 与 x 的亲近程度胜过 u 与 v

返回不开心的朋友的数目

## 解题思路

### 解法1（模拟（TLE））

使用一个哈希套哈希的结构来存储数据，方便查询，

将亲密度由大到小，转化为分数来保存，

遍历每一组统计其中的不开心人数，

``````c++
class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        int m = pairs.size();
        for (int i = 0; i < n; i++) {
            vector<int> tmp(preferences[i]);
            // 对每一项使用一个哈希表示其对应的亲密度
            unordered_map<int, int> cur;
            for (int j = 0; j < n - 1; j++) {
                cur.insert(make_pair(tmp[j], n - j));  // 这里将下标转化为亲密度
            }
            cache_.insert(make_pair(i, cur));
        }
        
        int res = 0;
        // 检查每一组，注意每个小朋友只能被被统计一次
        for (int i = 0; i < m; i++) {
            int x = pairs[i][0];
            int y = pairs[i][1];
            bool xok = false;
            bool yok = false;
            // 与其他组作比较
            for (int j = 0; j < m; j++) {
                if (i == j) {
                    continue;
                }
                
                int u = pairs[j][0];
                int v = pairs[j][1];
                if (!xok && Check(x, y, u, v)) {
                    xok = true;
                }
                if (!yok && Check(y, x, u, v)) {
                    yok = true;
                }
                if (xok && yok) {
                    break;
                }
            }
            if (xok) {
                res++;
            }
            if (yok) {
                res++;
            }
        }
        return res;
    }
    
 private:
    // 使用哈希套哈希来作缓存
    unordered_map<int, unordered_map<int, int>> cache_;
    
    bool Check(int x, int y, int u, int v) {
        unordered_map<int, int> xmap = cache_.at(x);
        unordered_map<int, int> ymap = cache_.at(y);
        unordered_map<int, int> umap = cache_.at(u);
        unordered_map<int, int> vmap = cache_.at(v);
        
        if (xmap.at(u) > xmap.at(y) && umap.at(x) > umap.at(v)) {
            return true;
        }
        if (xmap.at(v) > xmap.at(y) && vmap.at(x) > vmap.at(u)) {
            return true;
        }
        
        return false;
    }
};
``````

