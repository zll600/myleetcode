# [661. Image Smoother](https://leetcode.com/problems/image-smoother/)

## 题目

An **image smoother** is a filter of the size `3 x 3` that can be applied to each cell of an image by rounding down the  average of the cell and the eight surrounding cells (i.e., the average  of the nine cells in the blue smoother). If one or more of the  surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).

![img](https://assets.leetcode.com/uploads/2021/05/03/smoother-grid.jpg)

Given an `m x n` integer matrix `img` representing the grayscale of an image, return *the image after applying the smoother on each cell of it*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/05/03/smooth-grid.jpg)

```
Input: img = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[0,0,0],[0,0,0],[0,0,0]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2021/05/03/smooth2-grid.jpg)

```
Input: img = [[100,200,100],[200,50,200],[100,200,100]]
Output: [[137,141,137],[141,138,141],[137,141,137]]
Explanation:
For the points (0,0), (0,2), (2,0), (2,2): floor((100+200+200+50)/4) = floor(137.5) = 137
For the points (0,1), (1,0), (1,2), (2,1): floor((200+200+50+200+100+100)/6) = floor(141.666667) = 141
For the point (1,1): floor((50+200+200+200+200+100+100+100+100)/9) = floor(138.888889) = 138
```

 

**Constraints:**

- `m == img.length`
- `n == img[i].length`
- `1 <= m, n <= 200`
- `0 <= img[i][j] <= 255`

## 题目大意

*图像平滑器* 是大小为 `3 x 3` 的过滤器，用于对图像的每个单元格平滑处理，平滑处理后单元格的值为该单元格的平均灰度。

每个单元格的  *平均灰度* 定义为：该单元格自身及其周围的 `8` 个单元格的平均值，结果需 *向下取整*。（即，需要计算蓝色平滑器中 9 个单元格的平均值）。

如果一个单元格周围存在单元格缺失的情况，则计算平均灰度时不考虑缺失的单元格（即，需要计算红色平滑器中 4 个单元格的平均值）

给你一个表示图像灰度的 m x n 整数矩阵 img ，返回对图像的每个单元格平滑处理后的图像 。

## 解题思路

这道题目就是从每个位置开始，并求出周围其他八个位置（如果有的话），直接模拟就可以了

### Solution 1:


````c++
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        rows_ = img.size();
        cols_ = img[0].size();

        vector<vector<int>> res(rows_, vector<int>(cols_, cols_));
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                res[i][j] = Smooth(i, j, img);
            }
        }

        return res;
    }

 private:
    int rows_;
    int cols_;

    int Smooth(int i, int j, const vector<vector<int>>& img) {
        int cnt = 1;
        int sum = img[i][j];

        // top
        if (i - 1 >= 0) {
            ++cnt;
            sum += img[i - 1][j];

            // top left
            if (j - 1 >= 0) {
                ++cnt;
                sum += img[i - 1][j - 1];
            }
            // top right
            if (j + 1 < cols_) {
                ++cnt;
                sum += img[i - 1][j + 1];
            }
        }
        // bottom
        if (i + 1 < rows_) {
            ++cnt;
            sum += img[i + 1][j];

            // bottom left
            if (j - 1 >= 0) {
                ++cnt;
                sum += img[i + 1][j - 1];
            }
            // bottom right
            if (j + 1 < cols_) {
                ++cnt;
                sum += img[i + 1][j + 1];
            }
        }
        // left
        if (j - 1 >= 0) {
            ++cnt;
            sum += img[i][j - 1];
        }
        // right
        if (j + 1 < cols_) {
            ++cnt;
            sum += img[i][j + 1];
        }

        return sum / cnt;
    }
};
````
