# [492. Construct the Rectangle](https://leetcode-cn.com/problems/construct-the-rectangle/)

## 题目

A web developer needs to know how to design a web page's size. So, given a specific rectangular web page’s area, your job by now is to design a rectangular web page, whose length L and width W satisfy the following requirements:

1. The area of the rectangular web page you designed must equal to the given target area.
2. The width `W` should not be larger than the length `L`, which means `L >= W`.
3. The difference between length `L` and width `W` should be as small as possible.

Return *an array `[L, W]` where `L` and `W` are the length and width of the web page you designed in sequence.*

 

**Example 1:**

```
Input: area = 4
Output: [2,2]
Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
But according to requirement 2, [1,4] is illegal; according to requirement 3,  [4,1] is not optimal compared to [2,2]. So the length L is 2, and the width W is 2.
```

**Example 2:**

```
Input: area = 37
Output: [37,1]
```

**Example 3:**

```
Input: area = 122122
Output: [427,286]
```

 

**Constraints:**

- `1 <= area <= 107`

## 题目大意

作为一位web开发者， 懂得怎样去规划一个页面的尺寸是很重要的。 现给定一个具体的矩形页面面积，你的任务是设计一个长度为 L 和宽度为 W 且满足以下要求的矩形的页面。要求：

````
1. 你设计的矩形页面必须等于给定的目标面积。

2. 宽度 W 不应大于长度 L，换言之，要求 L >= W 。

3. 长度 L 和宽度 W 之间的差距应当尽可能小。
````

按顺序返回「L,W」，

## 解题思路

从平方根开始计算，只计算宽度，最后做商就是长度，

### Solution 1:

这种解法从平方根开始计算，可以减少计算量

````c++
class Solution {
public:
    vector<int> constructRectangle(int area) {
        int width = static_cast<int>(sqrt(area)); // 从平方根开始计算
        for (int i = width; i >= 1; --i) {
            if (area % i == 0) {
                return vector<int>{area / i, i};
            }
        }
        
        return vector<int>{area, 1}; // 这里随便返回，因为不会执行到这里
    }
};
````

