# [946. Validate Stack Sequences](https://leetcode.com/problems/validate-stack-sequences/)

## 题目

Given two integer arrays `pushed` and `popped` each with distinct values, return `true` *if this could have been the result of a sequence of push and pop operations on an initially empty stack, or* `false` *otherwise.*

 

**Example 1:**

```
Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4),
pop() -> 4,
push(5),
pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
```

**Example 2:**

```
Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.
```

 

**Constraints:**

- `1 <= pushed.length <= 1000`
- `0 <= pushed[i] <= 1000`
- All the elements of `pushed` are **unique**.
- `popped.length == pushed.length`
- `popped` is a permutation of `pushed`.

## 题目大意

给定两个不含重复数字的整数数组，一个pushed，一个popped，按照这样的操作顺序之后，能否能把栈清空

## 解题思路

* 这道题使用栈进行模拟，
  * 遍历pushed 数组，一直压栈，直到栈顶元素于 popped 匹配，
  * 然后一直出栈，知道栈顶元素与 popped不匹配，
  * 重复上面两步，直至遍历完整个 pushed 数组

## 代码

````c++
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> sta;
        int start = 0;
        int end = popped.size();
        for (int i = 0; i < pushed.size(); ++i) {
            sta.push(pushed[i]);
            while (!sta.empty() && start < end && sta.top() == popped[start]) {
                sta.pop(); 
                ++start;
            }
        }
        
        return start == end;
    }
};
````

