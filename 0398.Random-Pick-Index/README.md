# [398. Random Pick Index](https://leetcode-cn.com/problems/random-pick-index/)

Given an integer array `nums` with possible **duplicates**, randomly output the index of a given `target` number. You can assume that the given target number must exist in the array.

Implement the `Solution` class:

- `Solution(int[] nums)` Initializes the object with the array `nums`.
- `int pick(int target)` Picks a random index `i` from `nums` where `nums[i] == target`. If there are multiple valid i's, then each index should have an equal probability of returning.

 

**Example 1:**

```
Input
["Solution", "pick", "pick", "pick"]
[[[1, 2, 3, 3, 3]], [3], [1], [3]]
Output
[null, 4, 0, 2]

Explanation
Solution solution = new Solution([1, 2, 3, 3, 3]);
solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(1); // It should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(3); // It should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 104`
- `-231 <= nums[i] <= 231 - 1`
- `target` is an integer from `nums`.
- At most `104` calls will be made to `pick`.

## 题目大意

给定一个可能含有重复数字的数组，随机输出给定数字的索引，你可以假设给定的数字一定存在在数组中，

## 解题思路

这是一道设计数据结构的题目，

这里要解决的问题有：

* 同样的数需要放在一起，
* 要随机返回一个数的下标

### Solution 1: map

最直白的解法，使用空间换时间，这里注意随机数引擎需要在构造函数中进行初始化

````c++
class Solution {
public:
    Solution(vector<int>& nums) {
        const int len = nums.size();
        for (int i = 0; i < len; ++i) {
            data_[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        const int len = data_[target].size(); // 得到数字集合
        uniform_int_distribution<int> rand(0, len - 1); // 整数随机数
        return data_[target][rand(engine_)];
    }

 private:
    unordered_map<int, vector<int>> data_; // 数字，数字出现的下标的集合
    default_random_engine engine_; // 随机数引擎
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
````



### Solution 2: 蓄水池抽样

这种解法可以参考这篇题解：

https://leetcode-cn.com/problems/random-pick-index/solution/zhong-gui-zhong-ju-xu-shui-chi-chou-yang-random-re/

````c++
class Solution {
public:
    Solution(vector<int>& nums) {
        data_ = nums;
    }
    
    int pick(int target) {
        int cnt = 0;
        int idx = -1;
        const int len = data_.size();
        for (int i = 0; i < len; ++i) {
            if (data_[i] == target) {
                ++cnt; // 统计 target 的数目
                uniform_int_distribution<int> rand;
                if (rand(engine_) % cnt == 0) {
                    idx = i;
                }
            }
        }
        return idx;
    }

 private:
    vector<int> data_; // 存储数组
    default_random_engine engine_; // 随机数引擎
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
````

### Solution 3:

这种解法使用了 迭代器来节省空间，但是我不是很认可这种方法，所以我更推荐上面的解法

````c++
class Solution {
public:
    Solution(vector<int>& nums) {
        first_ = nums.begin();
        last_ = nums.end();
    }
    
    int pick(int target) {
        int idx = -1;
        int cnt = 0;
        for (auto iter = first_; iter != last_; ++iter) {
            if (*iter == target) {
                ++cnt;
                uniform_int_distribution rand;
                if (rand(engine_) % cnt == 0) {
                    idx = iter - first_;
                }
            }
        }
        return idx;
    }

 private:
    vector<int>::iterator first_;
    vector<int>::iterator last_;
    default_random_engine engine_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
````

