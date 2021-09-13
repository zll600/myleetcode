# [118. Pascal’s Triangle](https://leetcode.com/problems/pascals-triangle/)

## 题目

Given an integer `numRows`, return the first numRows of **Pascal's triangle**.

In **Pascal's triangle**, each number is the sum of the two numbers directly above it as shown:

![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

 

**Example 1:**

```
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

**Example 2:**

```
Input: numRows = 1
Output: [[1]]
```

 

**Constraints:**

- `1 <= numRows <= 30`

## 题目大意

给定一个整数表示行数 numRows，返回 杨辉三角形的前 numRows 行，

在杨辉三角中，每个数，由它上面的两个数构成

## 解题思路

* 这道题，我觉得应该先想想应该用那种数据结构来存储，在这个数据结构中怎样存储，想清楚这个，我觉得这道题目就不难了

## 代码

````c++
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;

        for (int i = 0; i < numRows; ++i) {
            vector<int> tmp;

            for (int j = 0; j < i + 1; ++j) {
                if (j == 0 || j == i) {
                    tmp.push_back(1);
                } else if (i > 1) {
                    tmp.push_back(triangle[i - 1][j - 1] + triangle[i - 1][j]);
                }
            }
            triangle.push_back(tmp);
        }

        return triangle;
    }
};
````

