# [412. Fizz Buzz](https://leetcode.com/problems/fizz-buzz/)

## 题目

Given an integer `n`, return *a string array* `answer` (**1-indexed**) *where*:

- `answer[i] == "FizzBuzz"` if `i` is divisible by `3` and `5`.
- `answer[i] == "Fizz"` if `i` is divisible by `3`.
- `answer[i] == "Buzz"` if `i` is divisible by `5`.
- `answer[i] == i` if non of the above conditions are true.

 

**Example 1:**

```
Input: n = 3
Output: ["1","2","Fizz"]
```

**Example 2:**

```
Input: n = 5
Output: ["1","2","Fizz","4","Buzz"]
```

**Example 3:**

```
Input: n = 15
Output: ["1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz","11","Fizz","13","14","FizzBuzz"]
```

 

**Constraints:**

- `1 <= n <= 104`

## 题目大意

给定一个整数 n，返回一个字符串数组 answer （从 1 开始）

* answer[i] == "FizzBuzz" 如果 i 可以同时别 3 和 5 整除
* answer[i] == "Fizz" 如果 i 可以被 3 整除
* answer[i] == "Buzz" 如果 i 可以被 5 整除
* answet[i] == i 如果上述条件没有满足

## 解题思路

这里需要注意顺序 必须先判断 3 ，再判断 5，因为同时满足 3 和 5 的位置先加 3 的部分，再加5 的部分

简单模拟即可

`````c++
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res(n);

        for (int i = 1; i <= n; ++i) {
            res[i - 1] = "";
            if (i % 3 == 0) {
                res[i -1] += "Fizz";
            }
            if (i % 5 == 0) {
                res[i - 1] += "Buzz";
            }

            if (res[i - 1] == "") {
                res[i - 1] += to_string(i);
            }
        }

        return res;
    }
};
`````

