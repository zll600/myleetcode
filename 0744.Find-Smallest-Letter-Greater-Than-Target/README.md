# [744. Find Smallest Letter Greater Than Target](https://leetcode-cn.com/problems/find-smallest-letter-greater-than-target/)

## 题目

Given a characters array `letters` that is sorted in **non-decreasing** order and a character `target`, return *the smallest character in the array that is larger than* `target`.

**Note** that the letters wrap around.

- For example, if `target == 'z'` and `letters == ['a', 'b']`, the answer is `'a'`.

 

**Example 1:**

```
Input: letters = ["c","f","j"], target = "a"
Output: "c"
```

**Example 2:**

```
Input: letters = ["c","f","j"], target = "c"
Output: "f"
```

**Example 3:**

```
Input: letters = ["c","f","j"], target = "d"
Output: "f"
```

**Example 4:**

```
Input: letters = ["c","f","j"], target = "g"
Output: "j"
```

**Example 5:**

```
Input: letters = ["c","f","j"], target = "j"
Output: "c"
```

 

**Constraints:**

- `2 <= letters.length <= 104`
- `letters[i]` is a lowercase English letter.
- `letters` is sorted in **non-decreasing** order.
- `letters` contains at least two different characters.
- `target` is a lowercase English letter.

## 题目大意

给定一个按照非降序排序的字母字符组成的数组，和一个目标字母，找到比目标字母大的最小的字母。

在比较时，字母是依序循环出现的。举个例子：

* 如果目标字母 `target = 'z'` 并且字符列表为 `letters = ['a', 'b']`，则答案返回 `'a'`

## 解题思路

我觉得这道题目是一道水题，总体还是不难的

### Solutoin 1:

````C++
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        for (char c : letters) {
            if (c > target) {
                return c;
            }
        }
        return letters[0];
    }
};
````



