# [636. Exclusive Time of Functions](https://leetcode.com/problems/exclusive-time-of-functions/)

## 题目

On a **single-threaded** CPU, we execute a program containing `n` functions. Each function has a unique ID between `0` and `n-1`.

Function calls are **stored in a [call stack](https://en.wikipedia.org/wiki/Call_stack)**: when a function call starts, its ID is pushed onto the stack, and when a function call ends, its ID is popped off the stack. The function whose  ID is at the top of the stack is **the current function being executed**. Each time a function starts or ends, we write a log with the ID, whether it started or ended, and the timestamp.

You are given a list `logs`, where `logs[i]` represents the `ith` log message formatted as a string `"{function_id}:{"start" | "end"}:{timestamp}"`. For example, `"0:start:3"` means a function call with function ID `0` **started at the beginning** of timestamp `3`, and `"1:end:2"` means a function call with function ID `1` **ended at the end** of timestamp `2`. Note that a function can be called **multiple times, possibly recursively**.

A function's **exclusive time** is the sum of execution  times for all function calls in the program. For example, if a function  is called twice, one call executing for `2` time units and another call executing for `1` time unit, the **exclusive time** is `2 + 1 = 3`.

Return *the **exclusive time** of each function in an array, where the value at the* `ith` *index represents the exclusive time for the function with ID* `i`.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2019/04/05/diag1b.png)

```
Input: n = 2, logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
Output: [3,4]
Explanation:
Function 0 starts at the beginning of time 0, then it executes 2 for units of time and reaches the end of time 1.
Function 1 starts at the beginning of time 2, executes for 4 units of time, and ends at the end of time 5.
Function 0 resumes execution at the beginning of time 6 and executes for 1 unit of time.
So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.
```

**Example 2:**

```
Input: n = 1, logs = ["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
Output: [8]
Explanation:
Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
Function 0 (initial call) resumes execution then immediately calls itself again.
Function 0 (2nd recursive call) starts at the beginning of time 6 and executes for 1 unit of time.
Function 0 (initial call) resumes execution at the beginning of time 7 and executes for 1 unit of time.
So function 0 spends 2 + 4 + 1 + 1 = 8 units of total time executing.
```

**Example 3:**

```
Input: n = 2, logs = ["0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"]
Output: [7,1]
Explanation:
Function 0 starts at the beginning of time 0, executes for 2 units of time, and recursively calls itself.
Function 0 (recursive call) starts at the beginning of time 2 and executes for 4 units of time.
Function 0 (initial call) resumes execution then immediately calls function 1.
Function 1 starts at the beginning of time 6, executes 1 unit of time, and ends at the end of time 6.
Function 0 resumes execution at the beginning of time 6 and executes for 2 units of time.
So function 0 spends 2 + 4 + 1 = 7 units of total time executing, and function 1 spends 1 unit of total time executing.
```

 

**Constraints:**

- `1 <= n <= 100`
- `1 <= logs.length <= 500`
- `0 <= function_id < n`
- `0 <= timestamp <= 109`
- No two start events will happen at the same timestamp.
- No two end events will happen at the same timestamp.
- Each function has an `"end"` log for each `"start"` log.

## 题目大意

有一个 *单线程 CPU* 正在运行一个含有 `n` 道函数的程序。每道函数都有一个位于  `0` 和 `n-1` 之间的唯一标识符。

函数调用 存储在一个 `调用栈` 上 ：当一个函数调用开始时，它的 *标识符* 将会推入栈中。而当一个函数调用结束时，它的标识符将会从栈中弹出。标识符位于栈顶的函数是 当前正在执行的函数 。每当一个函数开始或者结束时，将会记录一条日志，包括 *函数标识符* 、是 *开始还是结束* 、以及 *相应的时间戳*。

给你一个由日志组成的列表 `logs` ，其中 `logs[i]` 表示第 `i` 条日志消息，该消息是一个按 `"{function_id}:{"start" | "end"}:{timestamp}"` 进行格式化的字符串。例如，`"0:start:3"` 意味着标识符为 `0` 的函数调用在时间戳 `3` 的 起始开始执行；而 `"1:end:2"` 意味着标识符为 `1` 的函数调用在时间戳 `2` 的 末尾结束执行。注意，函数可以 *调用多次，可能存在递归调用* 。

函数的 *独占时间* 定义是在这个函数在程序所有函数调用中执行时间的总和，调用其他函数花费的时间不算该函数的独占时间。例如，如果一个函数被调用两次，一次调用执行 2 单位时间，另一次调用执行 1 单位时间，那么该函数的 独占时间 为 `2 + 1 = 3` 。

以数组形式返回每个函数的 *独占时间* ，其中第 `i` 个下标对应的值表示标识符 `i` 的函数的独占时间。

## 解题思路

函数的执行我们可以利用栈来模拟，这里栈顶始终表示正在执行的函数，这个函数如果执行结束就弹出，如果刚开始执行，就压栈，

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode.com/problems/exclusive-time-of-functions/submissions/)

````c++
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        std::tuple<int, string, int> last_log(-1, "", 0);
        // 模拟函数调用栈
        stack<tuple<int, string, int>> log_stack;
        
        // 遍历解析日志
        for (const string& log_str : logs) {
            std::tuple<int, string, int> log;
            SplitLog(log_str, log);
            
            // 如果上一条日志是 start，那么这条日志无论是什么结果都可以增加计时
            if ((std::get<1>(last_log) == "start" && std::get<1>(log) == "end")
               || (std::get<1>(last_log) == "start" && std::get<1>(log) == "start")) {
                res[std::get<0>(last_log)] += std::get<2>(log) - std::get<2>(last_log);
                
                // start:7 并且 end:7 是一分钟，不是 7 -7 = 0
                if (std::get<1>(log) == "end") {
                    ++res[std::get<0>(log)];
                }
            }
            
            // 如果上一条日志是 'end'，则如果这条日志是 'end'，则增加一定的时间
            if (std::get<1>(last_log) == "end" && std::get<1>(log) == "end") {
                res[std::get<0>(log)] += std::get<2>(log) - std::get<2>(last_log);
            }
            
            // 如果上一条日志是 'end'，这条日志是 'start'，如果新的函数不是立刻紧接着启动，
            // 且栈顶依旧还有在执行的函数，cpu 应该属于栈顶函数 则对栈顶增加一个段时间
            if (std::get<1>(last_log) == "end"
                && std::get<1>(log) == "start"
                && !log_stack.empty()) {
                res[std::get<0>(log_stack.top())] += std::get<2>(log) - std::get<2>(last_log) - 1;
            }
            
            if (std::get<1>(log) == "start") {
                // 如果是一个开始就入栈
                log_stack.push(log);
            } else {
                // 否则出栈
                log_stack.pop();
            }
            
            // last_log 不一定代表栈顶函数
            last_log = log;
        }
        
        return res;
    }
    
 private:
    // 解析日志到 tuple 中
    void SplitLog(const string& log_str, tuple<int, string, int>& log) {
        auto start = log_str.find_first_not_of(":", 0);
        auto pos = log_str.find_first_of(":", start);
        std::get<0>(log) = stoi(log_str.substr(0, pos - start));
        // cout << std::get<0>(log) << ":";
        
        start = log_str.find_first_not_of(":", pos);
        pos = log_str.find_first_of(":", start);
        std::get<1>(log) = std::move(log_str.substr(start, pos - start));
        // cout << std::get<1>(log) << ":";
        std::get<2>(log) = stoi(log_str.substr(pos + 1, log_str.size() - pos - 1));
        // cout << std::get<2>(log) << std::endl;
    }
};
````
