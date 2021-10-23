# [198. House Robber](https://leetcode.com/problems/house-robber/)

## 题目

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

Given an integer array `nums` representing the amount of money of each house, return *the maximum amount of money you can rob tonight **without alerting the police***.

 

**Example 1:**

```
Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
```

**Example 2:**

```
Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.
```

 

**Constraints:**

- `1 <= nums.length <= 100`
- `0 <= nums[i] <= 400`

## 题目大意

你是一个专业的小偷，计划去偷一条街的房子，每间房屋有一定数目的现金，唯一组织你偷每间房子的是相邻的两个房子间有安全系统相连，如果两间放在在一晚上同时被偷，会引发警报

给定一个数组表示每间房间的现金，返回不引起警报你能偷到的最多的钱

## 解题思路

这里也贴上一个错误的解法，记录自己犯过的错误，这中解法的定义了错误的状态，dp[i]为偷第 i 间房屋的最大钱数

比如这个用例就是错误的：**[2,1,1,2]**

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        const int size = nums.size();
        if (size < 2) {
            return nums[0];
        }
        
        vector<int> dp(size);
        dp[0] = nums[0];
        dp[1] = nums[1];
        
        int res = max(dp[0], dp[1]);
        for (int i = 2; i < size; ++i) {
            dp[i] = dp[i - 2] + nums[i];
            
            res = max(res, dp[i]);
        }
        
        return res;
    }
};
```

### Solution 1: DP

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/house-robber/solution/dong-tai-gui-hua-jie-ti-si-bu-zou-xiang-jie-cjavap/

* 状态定义：dp[i] 表示偷第前 i 间房屋的最大钱数，注意这里是前i 间，范围是 [0, i]，**但第 i 间不是必选**，这点很重要
* 状态转移：

```
dp[i] = max(dp[i -1], dp[i - 2] + nums[i])
```

* 初始化，需要初始化，初始化那些部分以及怎样初始化可以由**状态定义**和**转移方程**来决定
* 结果：dp[k]

`````
class Solution {
public:
    int rob(vector<int>& nums) {
        const int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        
        vector<int> dp(size);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < size; ++i) {
            dp[i] = max(dp[i -1], dp[i - 2] + nums[i]);
        }
        
        return dp[size - 1];
    }
};
`````

### Solution 3: 空间优化 dp

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        const int size = nums.size();
        if (size == 1) {
            return nums[0];
        }
        
        int first = nums[0];
        int second = max(nums[0], nums[1]);
        for (int i = 2; i < size; ++i) {
            int cur = max(second, first + nums[i]);
            first = second;
            second = cur;
        }
        
        return second;
    }
};
```

