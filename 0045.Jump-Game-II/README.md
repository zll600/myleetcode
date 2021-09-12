# [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/) 

## 题目

Given an array of non-negative integers `nums`, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

You can assume that you can always reach the last index.

 

**Example 1:**

```
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Example 2:**

```
Input: nums = [2,3,0,1,4]
Output: 2
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 1000`

## 题目大意

给定一个非负的整数数组，开始时，你在数组的第一个位置，数组中的每一个元素代表你可以从这个位置跳跃的最大距离，

你的目标是用最少的步数到达数组的最后一个位置，你可以假定一个一定可以到达最后哦一个位置，

## 解题思路

* 这是一道 贪心 的题目
* 在扫描数组的过程中，维护最远可以到达的位置，如果扫描的过程中遇到了边界，则需要增加步数

## 代码

`````c++
class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }
        
        int reach = 0;  // 可以到达的最远位置
        int steps = 0;  // 步数
        int end = 0;    // 这一步可以到达的边界，
        
        for (int i = 0; i < nums.size(); ++i) {
            if (i + nums[i] > reach) {
                reach = i + nums[i];    // 从当前位置跳一部，可以跳的最远位置
                if (reach >= nums.size() - 1) {
                    return steps + 1;
                }
            }
            
            if (i == end) { // 从但钱位置能跳到的最远位置，如果已经到则这里，说明需要多跳一部才可以，
                end = reach;
                ++steps;
            }
        }
        
        return steps;
    }
};
`````

