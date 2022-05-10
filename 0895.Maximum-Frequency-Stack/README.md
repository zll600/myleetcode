# [895. Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/)

## 题目

Design a stack-like data structure to push elements to the stack and pop the most frequent element from the stack.

Implement the `FreqStack` class:

- `FreqStack()` constructs an empty frequency stack.

- `void push(int val)` pushes an integer `val` onto the top of the stack.

- ```
  int pop()
  ```

   removes and returns the most frequent element in the stack. 

  - If there is a tie for the most frequent element, the element closest to the stack's top is removed and returned.

 

**Example 1:**

```
Input
["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop", "pop", "pop"]
[[], [5], [7], [5], [7], [4], [5], [], [], [], []]
Output
[null, null, null, null, null, null, null, 5, 7, 5, 4]

Explanation
FreqStack freqStack = new FreqStack();
freqStack.push(5); // The stack is [5]
freqStack.push(7); // The stack is [5,7]
freqStack.push(5); // The stack is [5,7,5]
freqStack.push(7); // The stack is [5,7,5,7]
freqStack.push(4); // The stack is [5,7,5,7,4]
freqStack.push(5); // The stack is [5,7,5,7,4,5]
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,5,7,4].
freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is closest to the top. The stack becomes [5,7,5,4].
freqStack.pop();   // return 5, as 5 is the most frequent. The stack becomes [5,7,4].
freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4 is closest to the top. The stack becomes [5,7].
```

 

**Constraints:**

- `0 <= val <= 109`
- At most `2 * 104` calls will be made to `push` and `pop`.
- It is guaranteed that there will be at least one element in the stack before calling `pop`.

## 题目大意

实现 `FreqStack`，模拟类似栈的数据结构的操作的一个类。

`FreqStack` 有两个函数：

- `push(int x)`，将整数 `x` 推入栈中。
- `pop()`，它移除并返回栈中出现最频繁的元素。如果最频繁的元素不只一个，则移除并返回最接近栈顶的元素。

## 解题思路

这种解法可以参考 [这篇题解](https://books.halfrost.com/leetcode/ChapterFour/0800~0899/0895.Maximum-Frequency-Stack/)

这里数据结构使用的是

- 每一个值 -> 对应的频数
- 每个频数 -> 贡献频数的值
- 动态维护最大的频数

````Go
type FreqStack struct {
    freq map[int]int
    group map[int][]int
    maxFreq int
}


func Constructor() FreqStack {
    // 存储频数
    freq := make(map[int]int)
    // 频数 -> 每一个数，按照进入的顺序
    group := make(map[int][]int)

    return FreqStack{freq: freq, group: group}
}


func (this *FreqStack) Push(val int)  {
    if _, ok := this.freq[val]; ok {
        this.freq[val]++
    } else {
        this.freq[val] = 1
    }

    cnt := this.freq[val]
    if cnt > this.maxFreq {
        this.maxFreq = cnt
    }
    this.group[cnt] = append(this.group[cnt], val)
}


func (this *FreqStack) Pop() int {
    tmp := this.group[this.maxFreq]
    val := tmp[len(tmp) - 1]
    this.group[this.maxFreq] = this.group[this.maxFreq][:len(tmp) - 1]
    this.freq[val]--
    if len(this.group[this.maxFreq]) == 0 {
        this.maxFreq--
    }
    return val
}


/**
 * Your FreqStack object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(val);
 * param_2 := obj.Pop();
 */

````
