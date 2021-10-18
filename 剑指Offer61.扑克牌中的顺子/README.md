# [剑指 Offer 61. 扑克牌中的顺子](https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/)

## 题目

从若干副扑克牌中随机抽 5 张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

 

示例 1:

输入: [1,2,3,4,5]
输出: True


示例 2:

输入: [0,0,1,2,5]
输出: True


限制：

数组长度为 5 

数组的数取值为 [0, 13] .

## 解题思路

这道题的关键在于

* 数组中不能出现重复
* 数组中的最大值 - 最小值 < 5

### Solution 1：排序 + 遍历

将数组按照升序排序之后，检测以下条件

* 数组中是否出现重复元素，出现重复直接返回
* 数组中是否出现 0，0 会影响最小值的位置

````c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // 按照升序排序
        const int size = nums.size();

        int joker = 0;  // 最小值的下标
        for (int i = 0; i < size; ++i) {
            if (nums[i] == 0) {
                joker++;
            } else if (i > 0 && nums[i] == nums[i - 1]) {  // 如果出现重复，直接返回
                return false;
            }
        }

        return nums[size - 1] - nums[joker] < 5;  // 是否符合条件
    }
};
````

### Solution 2:  unordered_set + 遍历

````c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        unordered_set<int> ht;  // 用 set 来实现去重
        int min_val = 14;
        int max_val = -1;

        const int size = nums.size();
        for (int i = 0; i < size; ++i) {
            if (nums[i] == 0) {
                continue;
            }

            min_val = min(min_val, nums[i]);  // 维护最大值
            max_val = max(max_val, nums[i]);  // 维护最小值
            if (ht.find(nums[i]) != ht.end()) {  // 如果找到，说明出现了重复，直接返回
                return false;
            }
            ht.insert(nums[i]);
        }

        return max_val - min_val < 5;
    }
};
````

