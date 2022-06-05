# [835. Image Overlap](https://leetcode.cn/problems/image-overlap/)

## 题目

You are given two images, `img1` and `img2`, represented as binary, square matrices of size `n x n`. A binary matrix has only `0`s and `1`s as values.

We **translate** one image however we choose by sliding all the `1` bits left, right, up, and/or down any number of units. We then place it on top of the other image. We can then calculate the **overlap** by counting the number of positions that have a `1` in **both** images.

Note also that a translation does **not** include any kind of rotation. Any `1` bits that are translated outside of the matrix borders are erased.

Return *the largest possible overlap*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/09/overlap1.jpg)

```
Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
Output: 3
Explanation: We translate img1 to right by 1 unit and down by 1 unit.

The number of positions that have a 1 in both images is 3 (shown in red).
```

**Example 2:**

```
Input: img1 = [[1]], img2 = [[1]]
Output: 1
```

**Example 3:**

```
Input: img1 = [[0]], img2 = [[0]]
Output: 0
```

 

**Constraints:**

- `n == img1.length == img1[i].length`
- `n == img2.length == img2[i].length`
- `1 <= n <= 30`
- `img1[i][j]` is either `0` or `1`.
- `img2[i][j]` is either `0` or `1`.

## 题目大意

给你两个图像 `img1` 和 `img2` ，两个图像的大小都是 `n x n` ，用大小相同的二进制正方形矩阵表示。二进制矩阵仅由若干 `0` 和若干 `1` 组成

转换 其中一个图像，将所有的 `1` 向左，右，上，或下滑动任何数量的单位；然后把它放在另一个图像的上面。该转换的 *重叠* 是指两个图像 都 具有 `1` 的位置的数目

请注意，转换 不包括 向任何方向旋转。越过矩阵边界的 1 都将被清除。

最大可能的重叠数量是多少？

## 解题思路

### Solution 1:

这种解法可以参考[这篇题解](https://leetcode.cn/problems/image-overlap/solution/835-cji-hu-shuang-bai-de-fan-xiang-jie-f-slhb/)

这种解法其实相当于暴力解法，计算 img1 中每个 1 转移到 img2 中每个可能的 1 产生的重合需要几步，不过这里是根据步数来分类，

其含义就是相同的水平方向的步数，垂直方向的步数，那么移动步骤一定是相同，那么只要找到这些分类中最大的即可

另外这里在计算移动的步数时要注意方向，可以规定向右和向下为正，那么这里为了使用数组来保存所有的结果，就需要对负方向的移动加上偏移量才行

````c++
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        const int n = img1.size();
        vector<vector<int>> diff(2 * n + 1, vector<int>(2 * n + 1));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (img1[i][j] == 1) {
                    for (int p = 0; p < n; ++p) {
                        for (int q = 0; q < n; ++q) {
                            if (img2[p][q] == 1) {
                                ++diff[i - p + n][j - q + n];
                            }
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < 2 * n + 1; ++i) {
            for (int j = 0; j < 2 * n + 1; ++j) {
                ans = max(ans, diff[i][j]);
            }
        }
        return ans;
    }
};
````

