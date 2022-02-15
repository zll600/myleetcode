# [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)

## 题目

Design and implement a data structure for a [Least Frequently Used (LFU)](https://en.wikipedia.org/wiki/Least_frequently_used) cache.

Implement the `LFUCache` class:

- `LFUCache(int capacity)` Initializes the object with the `capacity` of the data structure.
- `int get(int key)` Gets the value of the `key` if the `key` exists in the cache. Otherwise, returns `-1`.
- `void put(int key, int value)` Update the value of the `key` if present, or inserts the `key` if not already present. When the cache reaches its `capacity`, it should invalidate and remove the **least frequently used** key before inserting a new item. For this problem, when there is a **tie** (i.e., two or more keys with the same frequency), the **least recently used** `key` would be invalidated.

To determine the least frequently used key, a **use counter** is maintained for each key in the cache. The key with the smallest **use counter** is the least frequently used key.

When a key is first inserted into the cache, its **use counter** is set to `1` (due to the `put` operation). The **use counter** for a key in the cache is incremented either a `get` or `put` operation is called on it.

The functions `get` and `put` must each run in `O(1)` average time complexity.

 

**Example 1:**

```
Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3
```

 

**Constraints:**

- `0 <= capacity <= 104`
- `0 <= key <= 105`
- `0 <= value <= 109`
- At most `2 * 105` calls will be made to `get` and `put`.

## 题目大意

请你为 最不经常使用`（LFU）`缓存算法设计并实现数据结构。

实现 `LFUCache` 类：

- `LFUCache(int capacity)` - 用数据结构的容量 capacity 初始化对象
- `int get(int key)` - 如果键 `key` 存在于缓存中，则获取键的值，否则返回 `-1` 。
- `void put(int key, int value)` - 如果键 `key` 已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量 `capacity` 时，则应该在插入新项之前，移除最不经常使用的项。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 最近最久未使用 的键。

为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。

当一个键首次插入到缓存中时，它的使用计数器被设置为 `1 (由于 put 操作)`。对缓存中的键执行 `get` 或 `put` 操作，使用计数器的值将会递增。

函数 `get` 和 `put` 必须以 `O(1)` 的平均时间复杂度运行。

## 解题思路

要使得 `get 和 put` 的时间复杂度为 `O(1)`，那么必须要使用哈希表

这道题目可以参考 [这篇题解](https://leetcode.com/problems/lfu-cache/)


### Solution: O(log(n))


````c++
struct CacheNode {
    int key;
    int val;
    int freq;
    int tick;
    
    // 定义比较符号
    bool operator<(const CacheNode& rhs) const {
        if (freq < rhs.freq) {
            return true;
        } else if (freq == rhs.freq) {
            return tick < rhs.tick;
        }
        return false;
    }
};

class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity), tick_(0) {
    }
    
    int get(int key) {
        auto it = relat_.find(key);
        if (it == relat_.end()) {
            return -1;
        }
        
        int value = it->second.val;
        // 没操作一次都需要更新
        Touch(it->second);
        return value;
    }
    
    void put(int key, int value) {
        if (capacity_ == 0) {
            return;
        }
        
        auto it = relat_.find(key);
        if (it != relat_.end()) {
            // 如果存在直接更新
            it->second.val = value;
            Touch(it->second);
            return;
        }
        
        if (relat_.size() == capacity_) {
            // 如果容量已经满了，就删除使用频数最小，且计数最小的那个
            const CacheNode& node = *cache_.begin();
            relat_.erase(node.key);
            cache_.erase(node);
        }
        
        CacheNode node{key, value, 1, ++tick_};
        relat_[node.key] = node;
        cache_.insert(node);
    }
    
 private:
    int capacity_;  // 容量
    int tick_; // 递增的时间戳
    unordered_map<int, CacheNode> relat_; // key, value 的映射
    set<CacheNode> cache_; // 设置缓存
    
    void Touch(CacheNode& node) {
        // 先将原节点取出
        cache_.erase(node);
        // 更新
        ++node.freq;
        node.tick = ++tick_;
        // 再将原节点插入
        cache_.insert(node);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
````
