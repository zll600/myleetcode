# [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

## 题目

Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (`push`, `top`, `pop`, and `empty`).

Implement the `MyStack` class:

- `void push(int x)` Pushes element x to the top of the stack.
- `int pop()` Removes the element on the top of the stack and returns it.
- `int top()` Returns the element on the top of the stack.
- `boolean empty()` Returns `true` if the stack is empty, `false` otherwise.

**Notes:**

- You must use **only** standard operations of a queue, which means that only `push to back`, `peek/pop from front`, `size` and `is empty` operations are valid.
- Depending on your language, the queue may not be supported natively. You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.

 

**Example 1:**

```
Input
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
Output
[null, null, null, 2, 2, false]

Explanation
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // return 2
myStack.pop(); // return 2
myStack.empty(); // return False
```

 

**Constraints:**

- `1 <= x <= 9`
- At most `100` calls will be made to `push`, `pop`, `top`, and `empty`.
- All the calls to `pop` and `top` are valid.

## 题目大意

使用两个队列实现一个栈，要求满足一个正常栈的基本操作，

## 解题思路

* 在 push 的时候进行调整，
* 在 pop 的时候进行调整
* 可以用两个队列，也可以只用一个队列

## 代码

````c++
class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        while (!data.empty()) {
           backup.push(data.front());
           data.pop();
        }
        
        data.push(x);
        while (!backup.empty()) {
            data.push(backup.front());
            backup.pop();
        }
        
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int res = data.front();
        
        data.pop();
        
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return data.front();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return data.empty();
    }
    
private:
    queue<int> data;
    queue<int> backup;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
````

