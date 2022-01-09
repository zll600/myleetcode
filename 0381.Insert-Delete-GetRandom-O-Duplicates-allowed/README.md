# [381. Insert Delete GetRandom O(1) - Duplicates allowed](https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed/)

## 题目

`RandomizedCollection` is a data structure that contains a collection of numbers, possibly duplicates (i.e., a multiset). It should support inserting and removing specific elements and also removing a random element.

Implement the `RandomizedCollection` class:

- `RandomizedCollection()` Initializes the empty `RandomizedCollection` object.
- `bool insert(int val)` Inserts an item `val` into the multiset, even if the item is already present. Returns `true` if the item is not present, `false` otherwise.
- `bool remove(int val)` Removes an item `val` from the multiset if present. Returns `true` if the item is present, `false` otherwise. Note that if `val` has multiple occurrences in the multiset, we only remove one of them.
- `int getRandom()` Returns a random element from the current multiset of elements. The probability of each element being returned is **linearly related** to the number of same values the multiset contains.

You must implement the functions of the class such that each function works on **average** `O(1)` time complexity.

**Note:** The test cases are generated such that `getRandom` will only be called if there is **at least one** item in the `RandomizedCollection`.

 

**Example 1:**

```
Input
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]
Output
[null, true, false, true, 2, true, 1]

Explanation
RandomizedCollection randomizedCollection = new RandomizedCollection();
randomizedCollection.insert(1);   // return true since the collection does not contain 1.
                                  // Inserts 1 into the collection.
randomizedCollection.insert(1);   // return false since the collection contains 1.
                                  // Inserts another 1 into the collection. Collection now contains [1,1].
randomizedCollection.insert(2);   // return true since the collection does not contain 2.
                                  // Inserts 2 into the collection. Collection now contains [1,1,2].
randomizedCollection.getRandom(); // getRandom should:
                                  // - return 1 with probability 2/3, or
                                  // - return 2 with probability 1/3.
randomizedCollection.remove(1);   // return true since the collection contains 1.
                                  // Removes 1 from the collection. Collection now contains [1,2].
randomizedCollection.getRandom(); // getRandom should return 1 or 2, both equally likely.
```

 

**Constraints:**

- `-231 <= val <= 231 - 1`
- At most `2 * 105` calls **in total** will be made to `insert`, `remove`, and `getRandom`.
- There will be **at least one** element in the data structure when `getRandom` is called.

## 题目大意

`RandomizedCollection` 是一个包含可以重复的数字的集合，支持插入和删除特定值，同时支持随机删除值

实现 `RandomizedCollection` 类:

- `RandomizedCollection()` 初始化一个空对象

* `insert(val)`向集合中插入元素 `val`，即是 `val` 已经存在，如过 `val`，不存在返回 `true`，存在返回 `false`
* `remove(val)`当 `val` 存在时，从集合中移除一个 `val`，如果 `val` 存在，返回 `true`，否则返回 `false`，如果有多个 `val`，我们值删除其中一个
* `getRandom()`从现有集合中随机获取一个元素，每个元素被返回的概率应该与其在集合中的数量呈线性相关。


所有函数的*平均* 时间复杂度 **O(1)**

## 解题思路

这里的难点在于一个值可以存储多次，

### Solution 1:

这种解法可以参考花花的题解：http://zxi.mytechroad.com/blog/hashtable/leetcode-381-insert-delete-getrandom-o1-duplicates-allowed/

```c++
class RandomizedCollection {
public:
    RandomizedCollection() {
    }
    
    bool insert(int val) {
        relat_[val].push_back(vals_.size()); // 加入在数组中的索引
        vals_.emplace_back(val, relat_[val].size() - 1); // 在数组中构造
        return relat_[val].size() == 1U; // 只有第一次插入才返回 false
    }
    
    bool remove(int val) {
        if (relat_.find(val) == relat_.end()) {
            // 如果不存在，直接返回。false
            return false;
        }
        int index_to_evict = relat_[val].back();  // 拿出要删除的下标
        const auto& last_entry = vals_.back(); // 拿出数组中的最后一项
        
        relat_[last_entry.first][last_entry.second] = index_to_evict; // 修改最后一项的 哈希表
        swap(vals_[index_to_evict], vals_.back()); // 交换要删除的值和数组的组后一项
        
        vals_.pop_back(); // 删除对应的项
        relat_[val].pop_back(); // 删除对应的索引
        if (relat_[val].empty()) {
            // 如果这个 key，为空了，直接删除
            relat_.erase(val);  
        }
        return true;
    }
    
    int getRandom() {
        // 这里不是很懂
        return vals_[rand() % vals_.size()].first;
    }
    
 private:
    // val -> 在数组中的 index 
    unordered_map<int, vector<int>> relat_;
    // val, index 第几个数字
    vector<pair<int, int>> vals_;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```



