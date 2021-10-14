# [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

##  题目

Given a `rows x cols` binary `matrix` filled with `0`'s and `1`'s, find the largest rectangle containing only `1`'s and return *its area*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2020/09/14/maximal.jpg)

```
Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
```

**Example 2:**

```
Input: matrix = []
Output: 0
```

**Example 3:**

```
Input: matrix = [["0"]]
Output: 0
```

**Example 4:**

```
Input: matrix = [["1"]]
Output: 1
```

**Example 5:**

```
Input: matrix = [["0","0"]]
Output: 0
```

 

**Constraints:**

- `rows == matrix.length`
- `cols == matrix[i].length`
- `0 <= row, cols <= 200`
- `matrix[i][j]` is `'0'` or `'1'`.

## 题目大意

给定一个 rows x cols 的二进制矩阵，返回含有 1 的最大矩阵的面积

## 解题思路

这道题目可以参考这篇题解：https://leetcode-cn.com/problems/maximal-rectangle/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-1-8/

### 解法1（暴力）

具体的解决办法就是从当前行开始，先计算当前行开始，从这行开始向上计算，当然这里之解决了矩形高度的问题，对于矩形的宽度问题，这里使用了缓存的办法，使用一个二维数组保存每个位置所在行左侧连续的 1 的个数

`````c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) {
            return 0;
        }
        
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        int res = 0;
        vector<vector<int>> record(rows, vector<int>(cols));  // 存储每个位置，该行以该元素结尾的连续的 1 的数目
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                // 先更新 record
                if (matrix[row][col] == '1') {
                    if (col == 0) {
                        record[row][col] = 1;
                    } else {
                        record[row][col] = record[row][col - 1] + 1;
                    }
                } else {
                    record[row][col] = 0;
                }
                
                // 记录这里列上的最小宽度，
                int width = record[row][col];
                for (int up_row = row; up_row >= 0; --up_row) {  //从当前行，向上扩展，计算面积
                    int height = row - up_row + 1;
                    width = min(width, record[up_row][col]);
                    res = max(res, height * width);
                }
            }
        }
        
        return res;
    }
};
`````

### 解法2

这种解法使用的是类似于 84 题的做法，用两个数组分别存储该位置左边第一个比其小的，和右边第一个比其小的，然后作计算

`````c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) {
            return 0;
        }
        
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        int res = 0;
        vector<int> heights(cols, 0);
        
        for (int row = 0; row < rows; ++row) {
            // 计算 heights 数组
            for (int col = 0; col < cols; ++col) {
                if (matrix[row][col] == '1') {
                   ++heights[col];
                } else {
                    heights[col] = 0;
                }
            }
            
            // 更新 res
            res = max(res, LargestRectangle(heights));
        }
        
        return res;
    }
    
 private:
    int LargestRectangle(const vector<int>& heights) {
        if (heights.empty()) {
            return 0;
        }
        
        const int size = heights.size();
        // 找到每个位置左边第一个比其小的位置
        vector<int> left_less(size);
        left_less[0] = -1;  // 0 特殊处理
        for (int i = 1; i < size; ++i) {
            int left = i - 1;  // 向左找
            // 如果左边的比其大，继续向左
            while (left >= 0 && heights[left] >= heights[i]) {
                left = left_less[left];  // 利用已经计算过的，而不是重新计算
            }
            left_less[i] = left;
        }
        
        // 找到每一个位置右边的
        vector<int> right_less(size);
        right_less[size - 1] = size;  // size - 1 特殊处理
        for (int i = size - 2; i >= 0; --i) {
            int right = i + 1;  // 向右找
            while (right < size && heights[right] >= heights[i]) {
                right = right_less[right];
            }
            right_less[i] = right;
        }
        
        int res = 0;
        for (int i = 0; i < size; ++i) {
            int height = heights[i];
            res = max(res, height * (right_less[i] - left_less[i] - 1));
        }
        
        return res;
    }
};
`````

### 解法3（单调栈）

使用类似84 题的做法，这种做法，需要使用一个额外的数组存储每个位置的高度，然后按照84 题的做法，使用单调栈来求解

`````c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) {
            return 0;
        }
        
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        int res = 0;
        vector<int> heights(cols, 0);
        
        for (int row = 0; row < rows; ++row) {
            // 计算 heights 数组
            for (int col = 0; col < cols; ++col) {
                if (matrix[row][col] == '1') {
                   ++heights[col];
                } else {
                    heights[col] = 0;
                }
            }
            
            // 更新 res
            res = max(res, LargestRectangle(heights));
        }
        
        return res;
    }
    
 private:
    int LargestRectangle(const vector<int>& heights) {
        stack<int> sta;
        
        int res = 0;
        const int size = heights.size();
        for (int i = 0; i < size; ++i) {
            // 新的元素小于栈顶元素
            while (!sta.empty() && heights[i] < heights[sta.top()]) {
                // 栈顶高度
                int height = heights[sta.top()];
                sta.pop();
                // 左侧第一个小于当前高度的高度
                int left = sta.empty() ? -1 : sta.top();
                res = max(res, (i - left - 1) * height);
            }
            sta.push(i);
        }
        
        while (!sta.empty()) {
            int height = heights[sta.top()];
            sta.pop();
            int left = sta.empty() ? -1 : sta.top();
            res = max(res, (size - left - 1) * height);  // size 充当剩余元素的右边界
        }
        
        return res;
    }
};
`````

#### 解法4（动态规划）

这种解法，利用动态规划来求解左边第一个最矮的和右边第一个最矮的，这里理解起来有点难度，重点在于如果在某一行更新 dp 数组时，矩阵中对应位置为 0，则，可以认为在这一层的计算中，其高度就为 0，所以这个会使状态的更新有些困难

``````c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) {
            return 0;
        }
        
        const int rows = matrix.size();
        const int cols = matrix[0].size();
        int res = 0;
        
        vector<int> left_less(cols, -1);  // 左侧
        vector<int> right_less(cols, cols);
        vector<int> heights(cols, 0);
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (matrix[row][col] == '1') {
                    ++heights[col];
                } else {
                    heights[col] = 0;
                }
            }
            
            int boundary = -1;  // 初始化上次出现 0 的位置
            for (int col = 0; col < cols; ++col) {
                if (matrix[row][col] == '1') {
                    left_less[col] = max(left_less[col], boundary);  // 取二者中更靠近右边的
                } else {
                    // 遇到 0，那么该位置左边小于该位置的元素就在 -1 上
                    left_less[col] = -1;
                    // 更新边界
                    boundary = col;
                }
            }
            
            // 计算右边
            boundary = cols;
            for (int col = cols - 1; col >= 0; --col) {
                if (matrix[row][col] == '1') {
                    right_less[col] = min(right_less[col], boundary);  // 取二者中更靠近左边的
                } else {
                    // 遇到 0，说明该位置右边小于该位置的元素在 cols 上
                    right_less[col] = cols;
                    // 更新边界
                    boundary = col;
                }
            }
            
            // 更新结果
            for (int col = cols - 1; col >= 0; --col) {
                res = max(res, (right_less[col] - left_less[col] - 1) * heights[col]);
            }
        }
        
        return res;
    }
};
``````

