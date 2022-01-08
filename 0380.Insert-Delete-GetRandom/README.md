# [380. Insert Delete GetRandom O(1)](https://leetcode-cn.com/problems/insert-delete-getrandom-o1/)

## 题意

Implement the `RandomizedSet` class:

- `RandomizedSet()` Initializes the `RandomizedSet` object.
- `bool insert(int val)` Inserts an item `val` into the set if not present. Returns `true` if the item was not present, `false` otherwise.
- `bool remove(int val)` Removes an item `val` from the set if present. Returns `true` if the item was present, `false` otherwise.
- `int getRandom()` Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the **same probability** of being returned.

You must implement the functions of the class such that each function works in **average** `O(1)` time complexity.

 

**Example 1:**

```
Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
```

 

**Constraints:**

- `-231 <= val <= 231 - 1`
- At most `2 * 105` calls will be made to `insert`, `remove`, and `getRandom`.
- There will be **at least one** element in the data structure when `getRandom` is called.

## 题目大意

实现`RandomizedSet` 类：

* `RandomizedSet()` 初始化 `RandomizedSet` 对象
* `bool insert(int val)` 当元素 `val` 不存在时，向集合中插入该项，并返回 `true` ；否则，返回 `false` 。
* `bool remove(int val)` 当元素 `val` 存在时，从集合中移除该项，并返回 `true` ；否则，返回 `false` 。
* `int getRandom()` 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。

你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。



## 解题思路

这里要满足的是

* 添加和删除都是 O(1)，
* 每个元素等概率的返回，

### Solution 1:  unordered_map + vector

这道题可以参考花花的题解：https://www.youtube.com/watch?v=y240Qh9H9uk

或者这个：https://zxi.mytechroad.com/blog/category/data-structure/page/4/

很详细，随机数的部分我改了，理由也已经写在代码中了

```c++
class RandomizedSet {
public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if (relat_.find(val) != relat_.end()) {
            // 如果值已经存在
            return false;
        }
        relat_[val] = vals_.size(); // 添加一个新的值
        vals_.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (relat_.find(val) == relat_.end()) {
            // 如果哦值不存在，直接返回
            return false;
        }
        
        // 要删除的数和最后一个数交换位置
        int index = relat_[val];
        relat_[vals_.back()] = index;
        relat_.erase(val); // 从 map 中删除
        swap(vals_[index], vals_.back()); // 交换
        vals_.pop_back(); // 删除
        return true;
    }
    
    int getRandom() {
        // 随机数引擎不能在这里初始化，而应该在构造函数中初始化
        // default_random_engine rand;
        uniform_int_distribution<int> dis(0, vals_.size() - 1);
        return vals_[dis(rand_)];
    }
    
 private:
    unordered_map<int, int> relat_; // <val, val 在数组中的下标>
    vector<int> vals_; // 存储每个值，用于随机获取
    default_random_engine rand_; // 随机数引擎
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```



