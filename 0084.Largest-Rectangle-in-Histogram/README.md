# [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## 题目

Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return *the area of the largest rectangle in the histogram*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/01/04/histogram.jpg)

```
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/01/04/histogram-1.jpg)

```
Input: heights = [2,4]
Output: 4
```

 

**Constraints:**

- `1 <= heights.length <= 105`
- `0 <= heights[i] <= 104`

## 题目大意

给定一个数组代表直方图中每个矩形的高，每个矩形的宽均为 1，返回这个直方图中面积最大的矩形

## 解题思路

* 使用暴力解法，但是时间复杂度太高，超时
* 使用单调栈，这里要新建一个辅助数组，目的是加上两个哨兵，使得计算的时候向左扩，和向右扩都是都有一个终点，这里使用从栈底到栈顶递增的一个栈，如果遇到比当前栈顶还小的元素，就弹出当前栈顶，并计算以个矩形为中央的最大面积，其右边界就是当前遍历到的元素，右边界就是新的栈顶元素，看上去只算里两个矩形，实际上已弹出的这个没有向左扩到的，新的栈顶弹出后可以继续计算。重复这个操作，直到栈中没有大于当前遍历到的元素，每次弹出都计算并更新最终的结果，这里的题解，可以参考《左程云的书》。

## 代码

````c++
class Solution {
public:
    // 解法一：暴力搜索，超时，时间复杂度O(n^2)
    /*
    int largestRectangleArea(vector<int>& heights) {
        int area = 0;
        
        int size = heights.size();
        for (int i = 0; i < size; ++i) {
            int left = i;
            int cur = heights[i];
            while (left > 0 && heights[left - 1] >= cur) {
                --left;
            }
            
            int right = i;
            while (right < size - 1 && heights[right + 1] >= cur) {
                ++right;
            }
            
            area = max(area, cur * (right - left + 1));
        }
        
        return area;
    }*/
    
    // 解法二：利用单调栈来计算 时间复杂度 O(n),空间复杂度O(n)
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        vector<int> helper(size + 2, 0);
        for (int i = 0; i < size; ++i) {
            helper[i + 1] = heights[i];
        }
        
        stack<int> sta;
        int res = 0;
        for (int i = 0; i < size + 2; ++i) {
            while (!sta.empty() && helper[sta.top()] > helper[i]) {
                int idx = sta.top();
                sta.pop();
                res = max(res, helper[idx] * ((i - sta.top()) - 1));
            }
            sta.push(i);
        }
        
        return res;
    }
};
````

