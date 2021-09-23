# [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/)

## 题目

You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in **adjacent** plots.

Given an integer array `flowerbed` containing `0`'s and `1`'s, where `0` means empty and `1` means not empty, and an integer `n`, return *if* `n` new flowers can be planted in the `flowerbed` without violating the no-adjacent-flowers rule.

 

**Example 1:**

```
Input: flowerbed = [1,0,0,0,1], n = 1
Output: true
```

**Example 2:**

```
Input: flowerbed = [1,0,0,0,1], n = 2
Output: false
```

 

**Constraints:**

- `1 <= flowerbed.length <= 2 * 104`
- `flowerbed[i]` is `0` or `1`.
- There are no two adjacent flowers in `flowerbed`.
- `0 <= n <= flowerbed.length`

## 题目大意

你有一个很长的花坛，里面一些地块被种植，一些没有，然而，这些花不能被种在相邻的地方，

给定一个种有花的整数数组包括 0 和 1，其中 0 意味着空，1 意味中不空，

再 给定一个整数 n，返回这 n 朵花是否可以不用违反规则全被种进花坛

## 解题思路

这道题目是一道贪心的题目，如果当前位置可以种植一朵花就种一朵，

* 如果是数组的边界，只需要判断其前面或者后面是不是1
* 如果不是数组边界，则需要判断其前面和后面

这里贴上两篇题解：https://leetcode-cn.com/problems/can-place-flowers/solution/chong-hua-wen-ti-tan-xin-dang-qian-wei-z-959y/

https://leetcode-cn.com/problems/can-place-flowers/solution/fei-chang-jian-dan-de-tiao-ge-zi-jie-fa-nhzwc/

## 代码

`````c++
class Solution {
public:
    // 跳格子，不改变原数组
    bool canPlaceFlowers1(vector<int>& flowerbed, int n) {
        int i = 0;
        while (i < flowerbed.size() && n > 0) {
            if (flowerbed[i] == 1) {
                i += 2; // 当前已经种了，那么下一个位置肯定不能种，一次性跳两格
            } else if (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0) {
                --n;    // 当前不是 0，且前一个必定是0，应为遇到 1 是跳两步的
                i += 2; // 如果当前是最后一位置，或者下一个位置是 0，就可以种，种完跳两格
            } else {
                i += 3; // 如果不是 1，而且下一个位置是1，则直接一次性跳3 格
            }
        }
        
        return n <= 0;
    }
    
    // 需要改变原数组，也可以复制一下原数组
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        for (int i = 0; i < flowerbed.size(); ++i) {
            if (flowerbed[i] == 0
                && (i == 0 || flowerbed[i - 1] == 0)    // 如果不是第一个要考虑前一个
                && (i == flowerbed.size() - 1 || flowerbed[i + 1] == 0)) { // 如果不是最后一个，就要考虑下一个
                flowerbed[i] = 1;
                --n;
            }
        }
        
        return n <= 0;
    }
};
`````

