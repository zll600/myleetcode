# [384. Shuffle an Array](https://leetcode-cn.com/problems/shuffle-an-array/)

## 题目

Given an integer array `nums`, design an algorithm to randomly shuffle the array. All permutations of the array should be **equally likely** as a result of the shuffling.

Implement the `Solution` class:

- `Solution(int[] nums)` Initializes the object with the integer array `nums`.
- `int[] reset()` Resets the array to its original configuration and returns it.
- `int[] shuffle()` Returns a random shuffling of the array.

 

**Example 1:**

```
Input
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
Output
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // Shuffle the array [1,2,3] and return its result.
                       // Any permutation of [1,2,3] must be equally likely to be returned.
                       // Example: return [3, 1, 2]
solution.reset();      // Resets the array back to its original configuration [1,2,3]. Return [1, 2, 3]
solution.shuffle();    // Returns the random shuffling of array [1,2,3]. Example: return [1, 3, 2]
```

 

**Constraints:**

- `1 <= nums.length <= 200`
- `-106 <= nums[i] <= 106`
- All the elements of `nums` are **unique**.
- At most `5 * 104` calls **in total** will be made to `reset` and `shuffle`.

## 题目

给你一个整数数组 nums ，设计算法来打乱一个没有重复元素的数组。

实现 Solution class:

* `Solution(int[] nums)` 使用整数数组 `nums` 初始化对象
* `int[] reset()` 重设数组到它的初始状态并返回
* `int[] shuffle()` 返回数组随机打乱后的结果‘

## 解题思路

### Solution 1:

这道题考察了一个洗牌算法，这个我没有学过，这里放上一篇题解：https://leetcode-cn.com/problems/shuffle-an-array/solution/da-luan-shu-zu-yi-ding-gong-ping-de-xi-p-21iy/

```c++
class Solution {
public:
    Solution(vector<int>& nums) {
        original_ = nums;
    }
    
    vector<int> reset() {
        return original_;
    }
    
    vector<int> shuffle() {
        vector<int> nums(original_);                    //用原数组来初始化新数组

        for (int i = nums.size() - 1; ~i; i -- )       //从后往前遍历
        {
            swap(nums[i], nums[rand() % (i + 1)]);     //rand()能随机生成0到最大随机数的任意整数
        }                                              //rand() % (i + 1)能随机生成0到i中的任意整数

        return nums;

    }
    
 private:
    vector<int> original_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
```

