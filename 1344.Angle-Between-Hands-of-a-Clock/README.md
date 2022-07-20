#### [1344. Angle Between Hands of a Clock](https://leetcode.cn/problems/angle-between-hands-of-a-clock/)

## 题目

Given two numbers, `hour` and `minutes`, return *the smaller angle (in degrees) formed between the* `hour` *and the* `minute` *hand*.

Answers within `10-5` of the actual value will be accepted as correct.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/12/26/sample_1_1673.png)

```
Input: hour = 12, minutes = 30
Output: 165
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2019/12/26/sample_2_1673.png)

```
Input: hour = 3, minutes = 30
Output: 75
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2019/12/26/sample_3_1673.png)

```
Input: hour = 3, minutes = 15
Output: 7.5
```

 

**Constraints:**

- `1 <= hour <= 12`
- `0 <= minutes <= 59`

## 题目大意

给你两个数 hour 和 minutes 。请你返回在时钟上，由给定时间的时针和分针组成的较小角的角度（60 单位制）。

 

示例 1：

输入：hour = 12, minutes = 30
输出：165

示例 2：

输入：hour = 3, minutes = 30
输出；75

示例 3：

输入：hour = 3, minutes = 15
输出：7.5

示例 4：

输入：hour = 4, minutes = 50
输出：155

示例 5：

输入：hour = 12, minutes = 0
输出：0

 

提示：

    1 <= hour <= 12
    0 <= minutes <= 59
    与标准答案误差在 10^-5 以内的结果都被视为正确结果。



### 解题思路

先将时针作为整点来算，每个整点对应一个角度，然后分针本身对应一个角度，计算两者的差值，记作 a，计算分针的值对时针移动的贡献计算 b，然后分情况

- 如果时针角度大于分针，ans = a + b
- 如果时针角度小于分针，ans = (a - b)，这里一定要使用绝对值，否则可能会出现负值(eg, 7, 38)

需要注意的地方有

- 1 <= hour <= 12 按照这种方法 12 需要做对应处理，改为 0
- 题目要求选择较小的度数，则结果不可能大于平角，所以最终结果需要判断一下(eg, 1, 57)

### Solution 1:

代码在这里，变量名应该算有意义吧

````c++
class Solution:
    def angleClock(self, hour: int, minutes: int) -> float:
        if hour == 12:
            hour = 0
        hour_angle = hour / 12 * 360.00000
        minutes_angle = minutes / 60 * 360.00000
        
        dis = abs(hour_angle - minutes_angle)
        # print(f'{dis}')
        diff = minutes / 60 * 30
        # print(f'{diff}')
        
        ans = 0.0
        if minutes_angle <= hour_angle:
            ans = dis + diff
        else:
            ans = abs(dis - diff)
            
        return ans if ans <= 180.00000 else 360.00000 - ans
````

