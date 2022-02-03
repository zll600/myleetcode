# [432. All O`one Data Structure](https://leetcode-cn.com/problems/all-oone-data-structure/)

## 题目

Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.

Implement the `AllOne` class:

- `AllOne()` Initializes the object of the data structure.
- `inc(String key)` Increments the count of the string `key` by `1`. If `key` does not exist in the data structure, insert it with count `1`.
- `dec(String key)` Decrements the count of the string `key` by `1`. If the count of `key` is `0` after the decrement, remove it from the data structure. It is guaranteed that `key` exists in the data structure before the decrement.
- `getMaxKey()` Returns one of the keys with the maximal count. If no element exists, return an empty string `""`.
- `getMinKey()` Returns one of the keys with the minimum count. If no element exists, return an empty string `""`.

 

**Example 1:**

```
Input
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
Output
[null, null, null, "hello", "hello", null, "hello", "leet"]

Explanation
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "hello"
allOne.inc("leet");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "leet"
```

 

**Constraints:**

- `1 <= key.length <= 10`
- `key` consists of lowercase English letters.
- It is guaranteed that for each call to `dec`, `key` is existing in the data structure.
- At most `5 * 104` calls will be made to `inc`, `dec`, `getMaxKey`, and `getMinKey`.

## 题目大意

设计一个存储字符串计数的数据结构，返回计数最大和最小的字符串

所有的操作都需要在 `O(1)` 的时间复杂度内完成 

实现 `AllOne` 类：

- `AllOne()` 初始化数据结构对象
- `inc(String key)` 为字符串 `key` 的计数增加 `1`，如果 `key` 不存在，插入并将计数置为 `1`
- `dec(String key)` 减少字符串 `key` 的计数 `1`，如果递减之后计数 `0`，从数据结构中删除，保证 `key` 是存在在数据结构中
- `getMaxKey()` 返回计数最大的字符串，如果不存在，返回空字符串 `""`，
- `getMinKey()` 返回计数最小的字符串，如果不存在，就返回空字符串 `""`

## 解题思路

这里我们可以从这样几个方面来考虑
- O(1)的时间完成查询，可以使用 哈希表
- O(1)的时间完成插入和删除，可以使用链表

### Solution 1:

这种解法可以参考花花的 [题解](https://www.bilibili.com/video/BV1XW411d7qR?spm_id_from=333.999.0.0)

````c++
class AllOne {
public:
  /** Initialize your data structure here. */
  AllOne() {}
 
  /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
  void inc(string key) {
    auto it = m_.find(key);
    
    if (it == m_.end()) {
      if (l_.empty() || l_.front().value != 1) 
        l_.push_front({1, {key}});
      else
        l_.front().keys.insert(key);
      m_[key] = l_.begin();
      return;
    }
    
    auto lit = it->second;
    
    auto nit = next(lit);
    if (nit == l_.end() || nit->value != lit->value + 1)
      nit = l_.insert(nit, {lit->value + 1, {}});
    nit->keys.insert(key);
    m_[key] = nit;
    
    remove(lit, key);
  }
 
  /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
  void dec(string key) {
    auto it = m_.find(key);
    if (it == m_.end()) return;
    
    auto lit = it->second;
        
    if (lit->value > 1) {
      auto pit = prev(lit);
      if (lit == l_.begin() || pit->value != lit->value - 1)
        pit = l_.insert(lit, {lit->value - 1, {}});
      pit->keys.insert(key);
      m_[key] = pit;
    } else {
      // value == 1, remove from the data structure
      m_.erase(key);
    }
    
    remove(lit, key);    
  }
 
  /** Returns one of the keys with maximal value. */
  string getMaxKey() {
    return l_.empty() ? "" : *l_.back().keys.cbegin();
  }
 
  /** Returns one of the keys with Minimal value. */
  string getMinKey() {
    return l_.empty() ? "" : *l_.front().keys.cbegin();
  }
private:
  struct Node {  
    int value;
    unordered_set<string> keys;
  };
  
  list<Node> l_;
  unordered_map<string, list<Node>::iterator> m_;
  
  // Remove from old node.
  void remove(list<Node>::iterator it, const string& key) {
    it->keys.erase(key);
    if (it->keys.empty())
      l_.erase(it);
  }
};

````
