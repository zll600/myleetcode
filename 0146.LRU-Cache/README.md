# [146. LRU Cache](https://leetcode.com/problems/lru-cache/)

## 题目

Design a data structure that follows the constraints of a **[Least Recently Used (LRU) cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU)**.

Implement the `LRUCache` class:

- `LRUCache(int capacity)` Initialize the LRU cache with **positive** size `capacity`.
- `int get(int key)` Return the value of the `key` if the key exists, otherwise return `-1`.
- `void put(int key, int value)` Update the value of the `key` if the `key` exists. Otherwise, add the `key-value` pair to the cache. If the number of keys exceeds the `capacity` from this operation, **evict** the least recently used key.

The functions `get` and `put` must each run in `O(1)` average time complexity.

 

**Example 1:**

```
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
```

 

**Constraints:**

- `1 <= capacity <= 3000`
- `0 <= key <= 104`
- `0 <= value <= 105`
- At most 2` * 105` calls will be made to `get` and `put`.

## 解题思路

这道题的解法，可以参考花花酱的视频

get 和 put 的时间复杂度是 O(1) ，这里选用哈希表来实现

频繁的插入和删除，这里用双端链表来实现

将访问元素移动到第一位，这里用链表来实现

`````c++
class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {
    }
    
    int get(int key) {
        const auto it = ht_.find(key);
        
        // 如果没找到直接返回 -1
        if (it == ht_.end()) {
            return -1;
        }
        
        // 将元素重新放入链表头
        cache_.splice(cache_.begin(), cache_, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        const auto it = ht_.find(key);
        
        // 如果找到
        if (it != ht_.end()) {
            // 原地修改
            it->second->second = value;
            // 将节点重新放入链表头
            cache_.splice(cache_.begin(), cache_, it->second);
            // 返回
            return;
        }
        
        // 如果缓存已满，淘汰最久没有使用的
        if (cache_.size() == capacity_) {
            // 找到最久没有访问的
            const auto& last = cache_.back();
            // 解除映射
            ht_.erase(last.first);
            // 删除记录
            cache_.pop_back();
        }
        
        // 头插法
        cache_.emplace_front(key, value);
        // 建立一个新的映射
        ht_.emplace(key, cache_.begin());
    }
    
 private:
    int capacity_;
    list<pair<int, int>> cache_;
    unordered_map<int, list<pair<int, int>>::iterator> ht_;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
`````

