# [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)

## 题目

Design a time-based key-value data structure that can store multiple values for the same key at different time stamps and retrieve the key's value at a certain timestamp.

Implement the `TimeMap` class:

- `TimeMap()` Initializes the object of the data structure.
- `void set(String key, String value, int timestamp)` Stores the key `key` with the value `value `at the given time `timestamp`.
- `String get(String key, int timestamp)` Returns a value such that `set` was called previously, with `timestamp_prev <= timestamp`. If there are multiple such values, it returns the value associated with the largest `timestamp_prev`. If there are no values, it returns `""`.

 

**Example 1:**

```
Input
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
Output
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation
TimeMap timeMap = new TimeMap();
timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
timeMap.get("foo", 1);         // return "bar"
timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
timeMap.get("foo", 4);         // return "bar2"
timeMap.get("foo", 5);         // return "bar2"
```

 

**Constraints:**

- `1 <= key.length, value.length <= 100`
- `key` and `value` consist of lowercase English letters and digits.
- `1 <= timestamp <= 107`
- All the timestamps `timestamp` of `set` are strictly increasing.
- At most `2 * 105` calls will be made to `set` and `get`.

## 题目大意

设计一个基于时间的键值对的数据结构，可以在不同的时间戳存储同一个键的多个值，并针对特定时间戳检索对应的值，

实现 TimeMap类，

* `TimeMap()` 初始化这个数据结构的对象
* `void set(String key, String value, int timestamp)` 存储给定时间戳的键值对，

* `String get(String key, int timestamp)` 
  * 返回上次调用 set 存储的值，其中 timestamp_prev <= timestamp
  * 如果有多个这样的值，返回 timestamp_prev 最大的那个
  * 如果没有值，返回""

## 解题思路

这种题目需要考虑合适的数据结构，题目中要求不同时间的时间戳存储同一个键的多个值，我们可以想到，值和时间戳是一一对应的，并且由于时间戳有单调递增的特性，所以这里可以使用一个 map来存储`<value, timestamp>`，有了上面这一个组合，这一个 map可以对应一个键，这里无法利用有序的特性，所以，使用unordered_map 即可，

## Solution 1:

这种解法，参考了花花酱的：https://zxi.mytechroad.com/blog/hashtable/leetcode-981-time-based-key-value-store/

`````c++
class TimeMap {
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        // 添加元素，key 不能重复，value可以重复
        data_[key].emplace(std::move(value), std::move(timestamp));
    }
    
    string get(string key, int timestamp) {
        // 检查键是否存在，
        auto exist = data_.find(key);
        if (exist == data_.end()) {  如果不存在，直接返回空
            return "";
        }
        // 二分查找第一个大于 timestamp 的位置
        auto iter = exist->second.upper_bound(timestamp);
        if (iter == begin(exist->second)) {  // 如果没有小于等于 timestamp 的位置，直接返回false
            return "";
        }
        return prev(iter)->second;  // 返回第一个符合条件的
    }
    
 private:
    // 这里使用哈希表浅套map来实现，<key, <value, timestamp>>
    unordered_map<string, map<int, string>> data_;
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
`````

