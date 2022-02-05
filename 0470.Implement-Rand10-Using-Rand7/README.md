# [470. Implement Rand10() Using Rand7()](https://leetcode-cn.com/problems/implement-rand10-using-rand7/)

## 题目

Given the **API** `rand7()` that generates a uniform random integer in the range `[1, 7]`, write a function `rand10()` that generates a uniform random integer in the range `[1, 10]`. You can only call the API `rand7()`, and you shouldn't call any other API. Please **do not** use a language's built-in random API.

Each test case will have one **internal** argument `n`, the number of times that your implemented function `rand10()` will be called while testing. Note that this is **not an argument** passed to `rand10()`.

 

**Example 1:**

```
Input: n = 1
Output: [2]
```

**Example 2:**

```
Input: n = 2
Output: [2,8]
```

**Example 3:**

```
Input: n = 3
Output: [3,8,10]
```

 

**Constraints:**

- `1 <= n <= 105`

 

**Follow up:**

- What is the [expected value](https://en.wikipedia.org/wiki/Expected_value) for the number of calls to `rand7()` function?
- Could you minimize the number of calls to `rand7()`?

## 题目大意

给定一个 api `rand7()`，产生一个 `[1, 7]` 之间的随机数，编写一个函数 `rand10()` 产生一个 `[1, 10]` 内的随机数，你只能使用 `rand7()`，不能使用内置的 rand 函数 

## 解题思路

这里关键是需要让 `[1, 10]` 中的数等概率的出现

### Solution 1: Math

这道题目可以参考 [花花的题解](https://www.bilibili.com/video/BV1Ut411Z7KX?spm_id_from=333.999.0.0)


````c++
// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

class Solution {
public:
    int rand10() {
        int index = INT_MAX;
        while (index >= 40) {
            index = 7 * (rand7() - 1) + (rand7() - 1);
        }
        return index % 10 + 1;
    }
};
````

