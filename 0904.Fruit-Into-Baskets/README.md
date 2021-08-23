# [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/)

## 题目

You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array `fruits` where `fruits[i]` is the **type** of fruit the `ith` tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

- You only have **two** baskets, and each basket can only hold a **single type** of fruit. There is no limit on the amount of fruit each basket can hold.
- Starting from any tree of your choice, you must pick **exactly one fruit** from **every** tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
- Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array `fruits`, return *the **maximum** number of fruits you can pick*.

 

**Example 1:**

```
Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.
```

**Example 2:**

```
Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].
```

**Example 3:**

```
Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
```

**Example 4:**

```
Input: fruits = [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can pick from trees [1,2,1,1,2].
```

 

**Constraints:**

- `1 <= fruits.length <= 105`
- `0 <= fruits[i] < fruits.length`

## 题目大意

给定一个整数数组，数组的每一项代表一种水果，你只能选择两种水果，而且选出的元素必须时连续的，也就是滑动窗口求最长子数组，这个子数组中只可能出现两种值

## 解题思路

利用滑动窗口求出只包含两种值的最长子数组，可以重复，但是不能包含其他数字

* 窗口扩大的条件：
  * 如果下一个数之前在窗口中已经出现过，那么`right + 1` 可能等于 `left`，或者下个位置上的数出现的次数大于0，
  * 如果`right + 1` 不等于 `left`，则需要满足但前窗口中只有一种数，
* 窗口缩小时注意：
  * 如果缩小后窗口中只剩下一种数，就要增加可加入数的种类数
  * 减小该数出现的频率
* 更新最终结果的条件
  * 如果窗口中已经有两种数了
  * 或者右窗口已经数组最右了（防止出现一直重复的现象）

## 代码

````c++
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int size = fruits.size();
        
        unordered_map<int, int> freq;
        int left = 0;
        int right = 0;
        int counter = 1;
        int res = 1;
        
        ++freq[fruits[0]];
        while (left < size) {
            if (right + 1 < size
               && ((counter > 0 && fruits[left] != fruits[right + 1])
                   || fruits[left] == fruits[right + 1]
                   || freq[fruits[right + 1]] > 0)) {
                if (counter > 0 && fruits[left] != fruits[right + 1]) {
                    --counter;
                }
                ++right;
                ++freq[fruits[right]];
            } else {
                if (counter == 0 || right == size - 1) {
                    res = max(res, right - left + 1);
                }
                
                if (--freq[fruits[left]] == 0) {
                    ++counter;
                }
                ++left;
            }
        }
        
        return res;
    }
};
````

