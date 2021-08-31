# [155. Min Stack](https://leetcode.com/problems/min-stack/)

## 题目

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Implement the `MinStack` class:

- `MinStack()` initializes the stack object.
- `void push(val)` pushes the element `val` onto the stack.
- `void pop()` removes the element on the top of the stack.
- `int top()` gets the top element of the stack.
- `int getMin()` retrieves the minimum element in the stack.

 

**Example 1:**

```
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
```

 

**Constraints:**

- `-231 <= val <= 231 - 1`
- Methods `pop`, `top` and `getMin` operations will always be called on **non-empty** stacks.
- At most `3 * 104` calls will be made to `push`, `pop`, `top`, and `getMin`.

## 题目大意

这道题目要求设计一个栈，实现各种操作

## 解题思路

最常见的方法时利用双栈法来解决，一个栈存储元素，另一个栈存储最小值，这里特别时对于不同步的双栈法，有特别需要注意的地方

## 代码

````c++
// 双栈同步法：
/*
class MinStack {
public:
    MinStack() {
    }
    
    void push(int val) {
        data.push(val);
        if (small.empty() || small.top() > val) {
            small.push(val);
        } else {
            small.push(small.top());
        }
    }
    
    void pop() {
        data.pop();
        small.pop();
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return small.top();
    }
private:
    stack<int> data;
    stack<int> small;
};
*/

// 双栈不同步法：
class MinStack {
 public:
    MinStack() {
        
    }
    
    void push(int val) {
        data.push(val);
        if (small.empty() || small.top() >= val) { // 因为相等才出栈，所以条件时 >= 入栈
            small.push(val);
        }
    }
    void pop() {
        if (small.top() == data.top()) {
            small.pop();
        }
        data.pop();
    }
    
    int top() {
        return data.top();
    }
    int getMin() {
        return small.top();
    }
    
 private:
    stack<int> data;
    stack<int> small;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
````

