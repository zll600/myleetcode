# [733. Flood Fill](https://leetcode.com/problems/flood-fill/)

## 题目

An image is represented by an `m x n` integer grid `image` where `image[i][j]` represents the pixel value of the image.

You are also given three integers `sr`, `sc`, and `newColor`. You should perform a **flood fill** on the image starting from the pixel `image[sr][sc]`.

To perform a **flood fill**, consider the starting pixel, plus any pixels connected **4-directionally** to the starting pixel of the same color as the starting pixel, plus any pixels connected **4-directionally** to those pixels (also with the same color), and so on. Replace the color of all of the aforementioned pixels with `newColor`.

Return *the modified image after performing the flood fill*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2021/06/01/flood1-grid.jpg)

```
Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation: From the center of the image with position (sr, sc) = (1, 1) (i.e., the red pixel), all pixels connected by a path of the same color as the starting pixel (i.e., the blue pixels) are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected to the starting pixel.
```

**Example 2:**

```
Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, newColor = 2
Output: [[2,2,2],[2,2,2]]
```

 

**Constraints:**

- `m == image.length`
- `n == image[i].length`
- `1 <= m, n <= 50`
- `0 <= image[i][j], newColor < 216`
- `0 <= sr < m`
- `0 <= sc < n`

## 题目大意

有一幅用二维整数数组表示的图像，二维数组中的每个元素的值表示这个点的像素，给定一个新的值(sr, sc)，表示图像渲染的起点，和一个新的颜色 newcolor，你需要重新渲染这张图。

为了完成上色工作，从初始坐标开始，记录初始坐标的上下左右四个方向上像素值与初始坐标相同的相连像素点，接着再记录这四个方向上符合条件的像素点与他们对应四个方向上像素值与初始坐标相同的相连像素点，……，重复该过程。将所有有记录的像素点的颜色值改为新的颜色值。最后返回经过上色渲染后的图像。

## 解题思路

* 这个题的解法可以联系第79题，使用 DFS 来解决，不过这道题目不需要撤销状态的更改

## 代码

````c++
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int color = image[sr][sc];
        if (color == newColor) {
            return image;
        }
        
        rows = image.size();
        cols = image[0].size();
        
        DFS(image, sr, sc, newColor);
        return image;
    }
    
 private:
    int rows;
    int cols;
    
    vector<vector<int>> dirs = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    bool IsValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
    
    void DFS(vector<vector<int>>& image, int x, int y, int new_color) {
        if (image[x][y] == new_color) { // 如果遇到已经能够改过的颜色，则不用再进行状态的转移
            return;
        }
        int old = image[x][y];
        image[x][y] = new_color;
        
        for (const vector<int>& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (IsValid(nx, ny) && image[nx][ny] == old) {
                DFS(image, nx, ny, new_color);
            }
        }
    }
};
````

