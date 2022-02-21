# [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

## 题目



We are given an array `asteroids` of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

 

**Example 1:**

```
Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
```

**Example 2:**

```
Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.
```

**Example 3:**

```
Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
```

 

**Constraints:**

- `2 <= asteroids.length <= 104`
- `-1000 <= asteroids[i] <= 1000`
- `asteroids[i] != 0`

## 题目大意

给定一个整数数组 `asteroids`，表示在同一行的行星。

对于数组中的每一个元素，其绝对值表示行星的大小，正负表示行星的移动方向（正表示向右移动，负表示向左移动）。每一颗行星以相同的速度移动。

找出碰撞后剩下的所有行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。两颗移动方向相同的行星，永远不会发生碰撞

## 解题思路

这道题目在遍历整个 `asteroids` 时每次只需要判断上一次的最后一个和当前的这一个,所以可以考虑使用栈来模拟

那么接下来就需要考虑入栈和出栈的条件了:

以下情况可以入栈:

- 栈为空
- 栈顶为负数
    - 当前数为负数,一起向左,
    - 当前数为正数,相背
- 当前数为正数
    - 栈顶为正,一起向右,
    - 栈顶为负,相背

剩下的情况就需要处理碰撞了

- 如果绝对值相等,栈顶出栈
- 如果栈顶更大,那么不用出栈
- 如果当前数更大,考虑多次出栈

### Solution 1: Stack

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/asteroid-collision/solution/735xing-xing-peng-zhuang-ji-yu-zhan-qu-f-xpd1/)


````c++
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> sta; // 这里直接使用 vector 来模拟栈
        
        for (int asteroid : asteroids) {
            while (!sta.empty() && sta.back() > 0 && sta.back() < -asteroid) {
                sta.pop_back();
            }
            
            if (sta.empty() || sta.back() < 0 || asteroid > 0) {
                sta.push_back(asteroid);
            } else if (asteroid < 0 && sta.back() == -asteroid) {
                sta.pop_back();
            }
        }
        
        return sta;
    }
};
````
