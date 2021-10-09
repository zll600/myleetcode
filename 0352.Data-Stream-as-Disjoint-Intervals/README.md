# [352. Data Stream as Disjoint Intervals](https://leetcode.com/problems/data-stream-as-disjoint-intervals/)

## 题目

Given a data stream input of non-negative integers `a1, a2, ..., an`, summarize the numbers seen so far as a list of disjoint intervals.

Implement the `SummaryRanges` class:

- `SummaryRanges()` Initializes the object with an empty stream.
- `void addNum(int val)` Adds the integer `val` to the stream.
- `int[][] getIntervals()` Returns a summary of the integers in the stream currently as a list of disjoint intervals `[starti, endi]`.

 

**Example 1:**

```
Input
["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
[[], [1], [], [3], [], [7], [], [2], [], [6], []]
Output
[null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]

Explanation
SummaryRanges summaryRanges = new SummaryRanges();
summaryRanges.addNum(1);      // arr = [1]
summaryRanges.getIntervals(); // return [[1, 1]]
summaryRanges.addNum(3);      // arr = [1, 3]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
summaryRanges.addNum(7);      // arr = [1, 3, 7]
summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]
```

 

**Constraints:**

- `0 <= val <= 104`
- At most `3 * 104` calls will be made to `addNum` and `getIntervals`.

 

**Follow up:** What if there are lots of merges and the number of disjoint intervals is small compared to the size of the data stream?

## 题目大意

给定一个非负数的数据流输入，将目前为止看到的数据总结为不相交的区间

实现 SummaryRanges 类：

* SummaryRanges() 使用一个空数据流初始化对象。
* void addNum(int val) 向数据流中加入整数 val 。
* int[][] getIntervals() 以不相交区间 [starti, endi] 的列表形式返回对数据流中整数的总结。

## 解题思路

这道题可参考这篇题解：https://leetcode-cn.com/problems/data-stream-as-disjoint-intervals/solution/352-cchao-96de-shuang-mapzhi-bai-de-jie-dybnf/

只要选择的数据结构合适，就不很很难，

### 解法1

使用两个 map （这里要用到 map）有序的特性，分别维护多组区间的左右边界，每当要加入一个新的数的时候需要进行以下判断：

* val - 1 和 val + 1 同时存在，则最终的区间可以合并
* 只存在 val - 1，左区间可以向右扩
* 只存在 val + 1，右区间可以向左扩
* 都不存在，只能新建一个区间

````c++
class SummaryRanges {
public:
    SummaryRanges() {
    }
    
    void addNum(int val) {
        // 先检查是否覆盖
        // 先找右边界
        auto it = right2left_.lower_bound(val);
        if (it != right2left_.end()) {
            // 判断左边界
            if (it->second <= val) {
                return;
            }        
        }
        
        // 没有覆盖，进行分类讨论
        auto left = right2left_.find(val - 1);
        auto right = left2right_.find(val + 1);
        
        if (left != right2left_.end() && right != left2right_.end()) {
            // 可以合并为一个新区间
            int new_left = right2left_.at(val - 1);
            int new_right = left2right_.at(val + 1);
            
            // right2left_.insert(make_pair(new_right, new_left));
            // left2right_.insert(make_pair(new_left, new_right));
            // 如果是添加的话，若原来的键已经存在，则新的值不会被添加
            right2left_[new_right] = new_left;  // 这里是更新或添加，
            left2right_[new_left]  = new_right;  // 这里是更新或添加
            
            right2left_.erase(val - 1);  // 这里需要删除这一对
            left2right_.erase(val + 1);  // 这里需要删除这一对
        } else if (left != right2left_.end() && right == left2right_.end()) {
            // 可以扩充左区间的右边界
            int new_left  = right2left_.at(val - 1);
            left2right_[new_left] = val;
            // right2left_.insert(make_pair(val, new_left));
            right2left_[val] = new_left;  // 更新或添加爱
            
            right2left_.erase(val - 1);  // 这里需要删除这一对
        } else if (left == right2left_.end() && right != left2right_.end()) {
            // 可以扩充右区间的左边界
            
            int new_right = left2right_.at(val + 1);
            right2left_[new_right] = val;
            // left2right_.insert(make_pair(val, new_right));
            left2right_[val] = new_right;  // 更新或添加
            
            left2right_.erase(val + 1);  // 这里需要删除这一对
        } else {
            // 新建一对
            
            // 这里是明确的插入
            left2right_.insert(make_pair(val, val));
            right2left_.insert(make_pair(val, val));
        }
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        for (const auto& it : left2right_) {
            res.push_back(vector<int>({it.first, it.second}));
        }
        
        return res;
    }
    
 private:
    // <左边界， 右边界>
    map<int, int> left2right_;
    // <右边界， 左边界>
    map<int, int> right2left_;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
````

