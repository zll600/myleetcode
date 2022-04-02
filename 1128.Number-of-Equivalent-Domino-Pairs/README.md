# [1128. Number of Equivalent Domino Pairs](https://leetcode.com/problems/number-of-equivalent-domino-pairs/)

## 题目

Given a list of `dominoes`, `dominoes[i] = [a, b]` is **equivalent to** `dominoes[j] = [c, d]` if and only if either (`a == c` and `b == d`), or (`a == d` and `b == c`) - that is, one domino can be rotated to be equal to another domino.

Return *the number of pairs* `(i, j)` *for which* `0 <= i < j < dominoes.length`*, and* `dominoes[i]` *is **equivalent to*** `dominoes[j]`.

 

**Example 1:**

```
Input: dominoes = [[1,2],[2,1],[3,4],[5,6]]
Output: 1
```

**Example 2:**

```
Input: dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
Output: 3
```

 

**Constraints:**

- `1 <= dominoes.length <= 4 * 104`
- `dominoes[i].length == 2`
- `1 <= dominoes[i][j] <= 9`

## 题目大意

给你一个由一些多米诺骨牌组成的列表 `dominoes`。如果其中某一张多米诺骨牌可以通过旋转 `0` 度或 `180` 度得到另一张多米诺骨牌，我们就认为这两张牌是等价的。形式上，`dominoes[i] = [a, b]` 和 `dominoes[j] = [c, d]` 等价的前提是 `a==c` 且 `b==d`，或是 `a==d` 且 `b==c`。

在 `0 <= i < j < dominoes.length` 的前提下，找出满足 `dominoes[i]` 和 `dominoes[j]` 等价的骨牌对 `(i, j)` 的数量。

## 解题思路

这里关键是快速判断那两组中的元素是相同的，

### Solution 1: Bource Force

这种解法最终会超时，时间 复杂度过高

````c++
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        const int len = dominoes.size();
        
        int res = 0;
        for (int i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if (IsValid(dominoes, i, j)) {
                    ++res;
                }
            }
        }
        
        return res;
    }
    
 private:
    // 判断是否符合条件
    bool IsValid(const vector<vector<int>>& dominoes, int i, int j) {
        if (dominoes[i][0] == dominoes[j][0] && dominoes[i][1] == dominoes[j][1]) {
            return true;
        }
        
        if (dominoes[i][1] == dominoes[j][0] && dominoes[i][0] == dominoes[j][1]) {
            return true;   
        }
        
        return false;
    }
};
````

### Solution 2: hash

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/1100~1199/1128.Number-of-Equivalent-Domino-Pairs/)

这里通过将每一组的两个值hash 为两个两位数，来减少一层循环，可以降低时间复杂度


````c++
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        const int len = dominoes.size();
        
        int res = 0;
        unordered_map<int, int> buckets;
        for (const vector<int>& dominoe : dominoes) {
            // 这里将一组 hash 成为一个两位数
            int key = dominoe[0] * 10 + dominoe[1];
            int rotate_key = dominoe[1] * 10 + dominoe[0];
            
            // 如果二者不想等，才会有后面的步骤
            if (dominoe[0] != dominoe[1]) {
                // 之前是否存在，如果存在累加
                if (buckets[rotate_key] >  0) {
                    res += buckets[rotate_key];
                }
            }
            
            // 之前是否存在
            if (buckets[key] > 0) {
                res += buckets[key];
            }
            ++buckets[key];
        }
        
        return res;
    }
};
````
