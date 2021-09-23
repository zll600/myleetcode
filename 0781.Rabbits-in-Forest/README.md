# [781. Rabbits in Forest](https://leetcode.com/problems/rabbits-in-forest/)

## 题目

There is a forest with an unknown number of rabbits. We asked n rabbits **"How many rabbits have the same color as you?"** and collected the answers in an integer array `answers` where `answers[i]` is the answer of the `ith` rabbit.

Given the array `answers`, return *the minimum number of rabbits that could be in the forest*.

 

**Example 1:**

```
Input: answers = [1,1,2]
Output: 5
Explanation:
The two rabbits that answered "1" could both be the same color, say red.
The rabbit that answered "2" can't be red or the answers would be inconsistent.
Say the rabbit that answered "2" was blue.
Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.
```

**Example 2:**

```
Input: answers = [10,10,10]
Output: 11
```

 

**Constraints:**

- `1 <= answers.length <= 1000`
- `0 <= answers[i] < 1000`

## 题目大意

森林里有未知数量的兔子，其中一些兔子（可能是全部）告诉你还有多少其他的兔子和自己有相同的颜色。我们将这些回答放在 `answers` 数组里。

给定一个数组 answers，返回森林中兔子的最少数目，

## 解题思路

我们可以得到以下条件：

* 同一种颜色的兔子，数目应该是相同的，也就是说，我们应该让同一种颜色的兔子尽可能的多
* 如果我们累计的同一种颜色的兔子数量超出了 answert[i] + 1，也就是回答相同的兔子的数目超过了它们回答的值，那么说明有多种不同颜色的兔子有相同的数量，
* 我们先将原数组进行排序，然后记录相同的数出现的第一次，然后跳过后面相同的，且数量超过同一种的

## 代码

`````c++
class Solution {
public:
    int numRabbits(vector<int>& answers) {
        sort(answers.begin(), answers.end());
        
        int res = 0;
        for (int i = 0; i < answers.size(); ++i) {
            int cur = answers[i];   // 保存可以有多少个相同的 cur 不用添加
            res += cur + 1;
            
            // 跳过后面相同的连续的 cur
            while (cur-- > 0 && i + 1 < answers.size() && answers[i] == answers[i + 1]) {
                ++i;
            } 
        }
        return res;
    }
};
`````

