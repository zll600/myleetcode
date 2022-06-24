#### [1276. Number of Burgers with No Waste of Ingredients](https://leetcode.cn/problems/number-of-burgers-with-no-waste-of-ingredients/)

Given two integers `tomatoSlices` and `cheeseSlices`. The ingredients of different burgers are as follows:

- **Jumbo Burger:** `4` tomato slices and `1` cheese slice.
- **Small Burger:** `2` Tomato slices and `1` cheese slice.

Return `[total_jumbo, total_small]` so that the number of remaining `tomatoSlices` equal to `0` and the number of remaining `cheeseSlices` equal to `0`. If it is not possible to make the remaining `tomatoSlices` and `cheeseSlices` equal to `0` return `[]`.

 

**Example 1:**

```
Input: tomatoSlices = 16, cheeseSlices = 7
Output: [1,6]
Explantion: To make one jumbo burger and 6 small burgers we need 4*1 + 2*6 = 16 tomato and 1 + 6 = 7 cheese.
There will be no remaining ingredients.
```

**Example 2:**

```
Input: tomatoSlices = 17, cheeseSlices = 4
Output: []
Explantion: There will be no way to use all ingredients to make small and jumbo burgers.
```

**Example 3:**

```
Input: tomatoSlices = 4, cheeseSlices = 17
Output: []
Explantion: Making 1 jumbo burger there will be 16 cheese remaining and making 2 small burgers there will be 15 cheese remaining.
```

 

**Constraints:**

- `0 <= tomatoSlices, cheeseSlices <= 107`



### 题目大意

圣诞活动预热开始啦，汉堡店推出了全新的汉堡套餐。为了避免浪费原料，请你帮他们制定合适的制作计划。

给你两个整数 `tomatoSlices` 和 `cheeseSlices`，分别表示番茄片和奶酪片的数目。不同汉堡的原料搭配如下：

    巨无霸汉堡：4 片番茄和 1 片奶酪
    小皇堡：2 片番茄和 1 片奶酪

请你以 `[total_jumbo, total_small]`（[巨无霸汉堡总数，小皇堡总数]）的格式返回恰当的制作方案，使得剩下的番茄片 `tomatoSlices` 和奶酪片 `cheeseSlices` 的数量都是 `0`

如果无法使剩下的番茄片 `tomatoSlices` 和奶酪片 `cheeseSlices` 的数量为 `0`，就请返回 `[]`

### 解题思路

二元一次方程组，注意解必须是正整数，否则返回空结果

### Solution 1



````c++
class Solution {
public:
    vector<int> numOfBurgers(int tomato_slices, int cheese_slices) {
        if (tomato_slices % 2 != 0 || tomato_slices < 2 * cheese_slices
           || 4 * cheese_slices < tomato_slices) {
            return {};
        }
        return {tomato_slices / 2 - cheese_slices, 2 * cheese_slices - tomato_slices / 2};
    }
};
````





