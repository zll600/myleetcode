# [1725. Number Of Rectangles That Can Form The Largest Square](https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/)

## 题目

You are given an array `rectangles` where `rectangles[i] = [li, wi]` represents the `ith` rectangle of length `li` and width `wi`.

You can cut the `ith` rectangle to form a square with a side length of `k` if both `k <= li` and `k <= wi`. For example, if you have a rectangle `[4,6]`, you can cut it to get a square with a side length of at most `4`.

Let `maxLen` be the side length of the **largest** square you can obtain from any of the given rectangles.

Return *the **number** of rectangles that can make a square with a side length of* `maxLen`.

 

**Example 1:**

```
Input: rectangles = [[5,8],[3,9],[5,12],[16,5]]
Output: 3
Explanation: The largest squares you can get from each rectangle are of lengths [5,3,5,5].
The largest possible square is of length 5, and you can get it out of 3 rectangles.
```

**Example 2:**

```
Input: rectangles = [[2,3],[3,7],[4,3],[3,7]]
Output: 3
```

 

**Constraints:**

- `1 <= rectangles.length <= 1000`
- `rectangles[i].length == 2`
- `1 <= li, wi <= 109`
- `li != wi`

## 题目大意

给你一个数组 `rectangles` ，其中 `rectangles[i] = [li, wi]` 表示第 `i` 个矩形的长度为 `li` 、宽度为 `wi`  。如果存在 `k` 同时满足 `k <= li` 和 `k <= wi` ，就可以将第 `i` 个矩形切成边长为 `k` 的正方形

- 例如，矩形  [4,6] 可以切成边长最大为 4 的正方形

设 `maxLen` 为可以从矩形数组 `rectangles` 切分得到的 最大正方形  的边长。返回可以切出边长为 `maxLen` 的正方形的矩形 数目

## 解题思路

这里的解法就是维护一个最大值，遍历整个数组，一旦遇到更大值相等就重新开始计数，相等就累加计数

### Solutioin 1:

````c++
class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        int ans = 1;
        int max_len = min(rectangles[0][0], rectangles[0][1]);

        for (int i = 1; i < rectangles.size(); ++i) {
            int side = min(rectangles[i][0], rectangles[i][1]);
            if (side > max_len) {
                max_len = side;
                ans = 1;
            } else if (side == max_len) {
                ++ans;
            }
        }
        return ans;
    }
};
````



