# [135. Candy](https://leetcode.com/problems/candy/)

## 题目

There are `n` children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:

- Each child must have at least one candy.
- Children with a higher rating get more candies than their neighbors.

Return *the minimum number of candies you need to have to distribute the candies to the children*.

 

**Example 1:**

```
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
```

**Example 2:**

```
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
```

 

**Constraints:**

- `n == ratings.length`
- `1 <= n <= 2 * 104`
- `0 <= ratings[i] <= 2 * 104`

## 题目大意

有 n 个小孩站成一条线，每个小孩跟据被给定数组 ratings 付给一个 rating，

你需要按照哦啊以下要求给这些孩子分发糖果：

* 每个孩子至少有一颗糖
* 评分更高的孩子个到比相邻孩子更国的糖果

然会你需要分发给孩子的糖果的最小数目

## 解题思路

这道题需要满足

* 当前位置的分数 > 左侧，当前位置的糖果 > 左侧
* 当前位置的分数 > 右侧，当前位置的糖果 < 右侧

这道题用到的是贪心算法，只要找到最大值，同时满足左右的条件

## 代码

`````c++
class Solution {
public:
    
    int candy1(vector<int>& ratings) {
        vector<int> left(ratings.size(), 1);
        vector<int> right(ratings.size(), 1);
        
        for (int i = 1; i < ratings.size(); ++i) {
            if (ratings[i] > ratings[i - 1]) {
                left[i] = left[i - 1] + 1;
            }
        }
        
        int res = left[ratings.size() - 1];
        for (int i = ratings.size() - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                right[i] = right[i + 1] + 1;
            }
            res += max(left[i], right[i]);  // 这里选择两个中的最大值，就可以同时满足大于相邻位置
        }
        
        return res;
    }
    
    int candy(vector<int>& ratings) {
        vector<int> vals(ratings.size(), 1);
        
        for (int i = 1; i < ratings.size(); ++i) {
            if (ratings[i] > ratings[i - 1]) {
                vals[i] = vals[i - 1] + 1;
            }
        }
        
        int res = vals[ratings.size() - 1];
        for (int i = ratings.size() - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1] && vals[i] <= vals[i + 1]) { // 注意这里的条件
                vals[i] = vals[i + 1] + 1;
            }
            res += vals[i];
        }
        
        return res;
    }
};
`````

