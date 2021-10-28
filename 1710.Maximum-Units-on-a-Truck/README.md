# [1710. Maximum Units on a Truck](https://leetcode.com/problems/maximum-units-on-a-truck/)

## 题目

You are assigned to put some amount of boxes onto **one truck**. You are given a 2D array `boxTypes`, where `boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]`:

- `numberOfBoxesi` is the number of boxes of type `i`.
- `numberOfUnitsPerBoxi` is the number of units in each box of the type `i`.

You are also given an integer `truckSize`, which is the **maximum** number of **boxes** that can be put on the truck. You can choose any boxes to put on the truck as long as the number of boxes does not exceed `truckSize`.

Return *the **maximum** total number of **units** that can be put on the truck.*

 

**Example 1:**

```
Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
Output: 8
Explanation: There are:
- 1 box of the first type that contains 3 units.
- 2 boxes of the second type that contain 2 units each.
- 3 boxes of the third type that contain 1 unit each.
You can take all the boxes of the first and second types, and one box of the third type.
The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.
```

**Example 2:**

```
Input: boxTypes = [[5,10],[2,5],[4,7],[3,9]], truckSize = 10
Output: 91
```

 

**Constraints:**

- `1 <= boxTypes.length <= 1000`
- `1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000`
- `1 <= truckSize <= 106`

## 题目大意

你需要将一些数量的盒子放进一个卡车中，给定一个二维数组`boxTypes`，其中 `boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]` ：

- `numberOfBoxesi` 是类型 i 的箱子的数量。-
- `numberOfUnitsPerBoxi` 是类型 i 每个箱子可以装载的单元数量。

 整数 `truckSize` 表示卡车上可以装载 箱子 的 最大数量 。只要箱子数量不超过 `truckSize` ，你就可以选择任意箱子装到卡车上。返回卡车可以装载 单元 的 最大 总数。

## 解题思路

其实我第一想法是使用动态规划，但是后来发现是贪心算法

### Solution 1: Greedy

这种解法可以参考霜神的题解：https://books.halfrost.com/leetcode/ChapterFour/1700~1799/1710.Maximum-Units-on-a-Truck/

就是贪心的优先选取可存放单元数最大的盒子

````c++
class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        // 先按照每种箱子可以放单元的数目来排序
        sort(boxTypes.begin(), boxTypes.end(), [](const vector<int>& a, const vector<int>& b) -> bool {
            return a[1] > b[1];
        });
        
        const int size = boxTypes.size();
        int boxes = 0;  // 使用的盒子的数目
        int units = 0;  // 可以放置的单元的数目
        int i = 0;
        // 贪心的优先选取可存放单元数目的最大的盒子
        while (i < size && boxes < truckSize) {
            // 遍历每一种盒子
            int cnt = boxTypes[i][0];
            while (cnt-- > 0 && boxes < truckSize) {
                units += boxTypes[i][1];
                ++boxes;
            }
            ++i;
        }
        
        return units;
    }
};
````

