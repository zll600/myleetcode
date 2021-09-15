# [528. Random Pick with Weight](https://leetcode.com/problems/random-pick-with-weight/)

## 题目

You are given an array of positive integers `w` where `w[i]` describes the weight of `i``th` index (0-indexed).

We need to call the function `pickIndex()` which **randomly** returns an integer in the range `[0, w.length - 1]`. `pickIndex()` should return the integer proportional to its weight in the `w` array. For example, for `w = [1, 3]`, the probability of picking the index `0` is `1 / (1 + 3) = 0.25` (i.e 25%) while the probability of picking the index `1` is `3 / (1 + 3) = 0.75` (i.e 75%).

More formally, the probability of picking index `i` is `w[i] / sum(w)`.

 

**Example 1:**

```
Input
["Solution","pickIndex"]
[[[1]],[]]
Output
[null,0]

Explanation
Solution solution = new Solution([1]);
solution.pickIndex(); // return 0. Since there is only one single element on the array the only option is to return the first element.
```

**Example 2:**

```
Input
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
Output
[null,1,1,1,1,0]

Explanation
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // return 1. It's returning the second element (index = 1) that has probability of 3/4.
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 1
solution.pickIndex(); // return 0. It's returning the first element (index = 0) that has probability of 1/4.

Since this is a randomization problem, multiple answers are allowed so the following outputs can be considered correct :
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
and so on.
```

 

**Constraints:**

- `1 <= w.length <= 10000`
- `1 <= w[i] <= 10^5`
- `pickIndex` will be called at most `10000` times.

## 题目大意

给定一个正整数数组，元素 i 代表位置 i 得权重，编写一个函数根据权重值返回数组对应的下标

## 解题思路

* 这道题目可以当作一道前缀和的题目来做
* 在[0， Prefixsum)中，随机产生一个数，下标 x 是满足 x <  PrefixSum[i] 的最小下标，求这个下标 i 即是最终解，通过二分查找来找出结果，对于某些下标 I，所有的满足prefixsum[i] - w[i] < x < prefixsum[i] 的 x 都映射到这个下标，所有的下标都与下标权重成比例，

## 代码

````c++
class Solution {
public:
    Solution(vector<int>& w) {
        // partial_sum(w.begin(), w.end(), back_inserter(sum));
        sum.push_back(w[0]);
        for (int i = 1; i < w.size(); ++i) {
            sum.push_back(sum.back() + w[i]);
        }
    }
    
    int pickIndex() {
        int weight = rand() % sum.back();
        return upper_bound(sum.begin(), sum.end(), weight) - sum.begin();
    }
    
 private:
    vector<int> sum;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */++
````

