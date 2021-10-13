# [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

## 题目

Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)

```
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
```

**Example 2:**

```
Input: height = [4,2,0,3,2,5]
Output: 9
```

 

**Constraints:**

- `n == height.length`
- `1 <= n <= 2 * 104`
- `0 <= height[i] <= 105`

## 题目大意

给定一个非负整数的数组表示一个条形图，其宽度为1，计算下雨之后，能容纳多少水

## 解题思路

这道题的解法，可以参考这篇题解：

https://leetcode-cn.com/problems/trapping-rain-water/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-8/

### 解法1（单调栈）

这个解法可以参考这篇题解：https://leetcode-cn.com/problems/trapping-rain-water/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-w-8/

具体做法是维护一个单调递减的单调栈，如果新元素大于栈顶元素，说明有可能可以接到雨水，所以出栈进行计算

模拟以下可以发现，这里出栈进行计算，其实是一层一层计算的，建议自己动手去模拟

如果元素为0，那就按0 算

每次计算的时候，高度是新栈顶和当前元素中最小的一个（木桶效应），宽度是 right - left - 1，计算面积，更新最大值

`````c++
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> sta;  //  这里利用一个单调递减的单调栈
        const int size = height.size();
        
        for (int i = 0; i < size; ++i) {
            while (!sta.empty() && height[sta.top()] < height[i]) {  // 如果遇到比栈顶大的元素，则出栈计算
                int cur = sta.top();  // 当前栈顶元素
                sta.pop();
                if (sta.empty()) {  // 如果栈为空，跳出循环
                    break;
                }
                int left = sta.top();  // 新的栈顶
                int right = i;
                int h = min(height[right], height[left]) - height[cur];  // 取最小的高度，做差
                ans += (right - left - 1) * h;  // 计算面积
            }
            sta.push(i);  // 新的位置入栈
        }
        
        return ans;
    }
};
`````

### 解法2（按行算）

