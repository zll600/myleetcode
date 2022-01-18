# [403. Frog Jump](https://leetcode-cn.com/problems/frog-jump/)

## 题目

A frog is crossing a river. The river is divided into some number of units, and at each unit, there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the water.

Given a list of `stones`' positions (in units) in sorted **ascending order**, determine if the frog can cross the river by landing on the last stone. Initially, the frog is on the first stone and assumes the first jump must be `1` unit.

If the frog's last jump was `k` units, its next jump must be either `k - 1`, `k`, or `k + 1` units. The frog can only jump in the forward direction.

 

**Example 1:**

```
Input: stones = [0,1,3,5,6,8,12,17]
Output: true
Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.
```

**Example 2:**

```
Input: stones = [0,1,2,3,4,8,9,11]
Output: false
Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.
```

 

**Constraints:**

- `2 <= stones.length <= 2000`
- `0 <= stones[i] <= 231 - 1`
- `stones[0] == 0`
- `stones` is sorted in a strictly increasing order.

## 题目大意

一只青蛙想要过河。 假定河流被等分为若干个单元格，并且在每一个单元格内都有可能放有一块石子（也有可能没有）。 青蛙可以跳上石子，但是不可以跳入水中。

给你石子的位置列表 stones（用单元格序号 升序 表示）， 请判定青蛙能否成功过河（即能否在最后一步跳至最后一块石子上）。

开始时， 青蛙默认已站在第一块石子上，并可以假定它第一步只能跳跃一个单位（即只能从单元格 1 跳至单元格 2 ）。

如果青蛙上一步跳跃了 k 个单位，那么它接下来的跳跃距离只能选择为 k - 1、k 或 k + 1 个单位。 另请注意，青蛙只能向前方（终点的方向）跳跃。



## 解题思路

这道题目可以很明显的看出来状态转移，所以可以考虑使用 回溯法来做

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/frog-jump/solution/shou-hua-tu-jie-ji-hao-de-di-gui-ti-man-8kk2z/

### Solution 1: DFS

这种解法最终是会超时的

```c++
class Solution {
public:
    bool canCross(vector<int>& stones) {
        return Backtracking(stones, 0, 0);
    }
    
 private:
    // 状态转移涉及到两个变量
    // idx 遍历到那个元素
    // k 上次跳过多少个单元格
    bool Backtracking(const vector<int>& stones, int idx, int k) {
        const int len = stones.size();
        for (int i = idx + 1; i < len; ++i) {
            int gap = stones[i] - stones[idx];
            if (gap >= k - 1 && gap <= k + 1) {
                // 一路递归，看能否到达
                if (Backtracking(stones, i, gap)) {
                    return true;
                }
            } else if (gap >= k + 1) {
                break;
            }
        }
        
        return idx == stones.size() - 1; // 如果递归到最后一个位置，则说明可达
    }
};
```



### Solution 2: 记忆化递归

解法 1 中存在大量的重复计算，所以这里的话，使用 缓存来加速查找

````c++
// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html template
template <typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T> inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template <typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};

class Solution {
public:
    bool canCross(vector<int>& stones) {
        return Backtracking(stones, 0, 0);
    }
    
 private:
    unordered_map<pair<int, int>, bool, pair_hash> cache_; // 缓存
    
    // 状态转移涉及到两个变量
    // idx 遍历到那个元素
    // k 上次跳过多少个单元格
    bool Backtracking(const vector<int>& stones, int idx, int k) {
        const pair<int, int> key = make_pair(idx, k); // 构造一个 key
        if (cache_.find(key) !=  cache_.end()) {
            // 如果 key 已经存在，说明之前到达过这里，但是无法继续递归，直接返回
            return false;
        } else {
            // 如果是第一次到达，直接返回
            cache_[key] = true;
        }
        
        const int len = stones.size();
        for (int i = idx + 1; i < len; ++i) {
            int gap = stones[i] - stones[idx];
            if (gap >= k - 1 && gap <= k + 1) {
                // 一路递归，看能否到达
                if (Backtracking(stones, i, gap)) {
                    return true;
                }
            } else if (gap >= k + 1) {
                break;
            }
        }
        
        return idx == stones.size() - 1; // 如果递归到最后一个位置，则说明可达
    }
};
````







