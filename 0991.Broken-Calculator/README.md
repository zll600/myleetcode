# [991. Broken Calculator](https://leetcode.com/problems/broken-calculator/)

## 题目

There is a broken calculator that has the integer `startValue` on its display initially. In one operation, you can:

- multiply the number on display by `2`, or
- subtract `1` from the number on display.

Given two integers `startValue` and `target`, return *the minimum number of operations needed to display* `target` *on the calculator*.

 

**Example 1:**

```
Input: startValue = 2, target = 3
Output: 2
Explanation: Use double operation and then decrement operation {2 -> 4 -> 3}.
```

**Example 2:**

```
Input: startValue = 5, target = 8
Output: 2
Explanation: Use decrement and then double {5 -> 4 -> 8}.
```

**Example 3:**

```
Input: startValue = 3, target = 10
Output: 3
Explanation: Use double, decrement and double {3 -> 6 -> 5 -> 10}.
```

 

**Constraints:**

- `1 <= startValue, target <= 109`

## 题目大意

在显示着数字 `startValue` 的坏计算器上，我们可以执行以下两种操作：

- 将显示屏上的数字乘 2；
- 将显示屏上的数字减 1 。

最初，计算器显示数字 `startValue`。返回显示数字 `target` 所需的最小操作数。

## 解题思路

这道题目可以参考这几篇题解：

- https://leetcode-cn.com/problems/broken-calculator/solution/tan-xin-suan-fa-ji-qi-zheng-ming-by-lenn123/
- https://leetcode-cn.com/problems/broken-calculator/solution/ni-xiang-tan-xin-jie-fa-c-by-zhouzihong-cox9/
- https://leetcode-cn.com/problems/broken-calculator/solution/js-di-gui-by-marswiz-6yxm/

### Solution 1: Greedy

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0900~0999/0991.Broken-Calculator/)

这里利用贪心的思想，尽可能的使用 乘 2 来加速调整，然后使用 减 1 来进行微调

````c++
class Solution {
public:
    int brokenCalc(int start_value, int target) {
        int res = 0;
        
        while (start_value < target) {
            ++res;
            if ((target & 1) == 1) {
                ++target;
            } else {
                target /= 2;
            }
        }
        
        return res + start_value - target;
    }
};
````

