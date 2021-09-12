# [55. Jump Game](https://leetcode.com/problems/jump-game/)

## 题目

You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element in the array represents your maximum jump length at that position.

Return `true` *if you can reach the last index, or* `false` *otherwise*.

 

**Example 1:**

```
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Example 2:**

```
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
```

 

**Constraints:**

- `1 <= nums.length <= 104`
- `0 <= nums[i] <= 105`

## 题目大意

给定一个整数数组，初始时，你在第一个下标的位置，数组的每个元素表示你可以从这个位置跳多远

如果你可以到达最后一个位置，返回true，如果不能返回 false，

## 解题思路

* 这道题目其实使用的是贪心的思想，
* 维护一个可以到达的最远位置，如果当前位置已经超出，则直接返回错误即可，如果没有更新最远位置

## 代码

`````c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() == 1) {
            return true;
        }
        
        int go = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i > go) {   // 先判断，如果无法到啊当前位置，则直接返回
                return false; 
            }
            go = max(go, i + nums[i]); // 必须先做判断，才可进行更新
        }
        return true;
    }
};
`````

