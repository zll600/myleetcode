# [682. Baseball Game](https://leetcode.com/problems/baseball-game/)

## 题目

You are keeping score for a baseball game with strange rules. The game consists of several rounds, where the scores of past rounds may affect future rounds' scores.

At the beginning of the game, you start with an empty record. You are given a list of strings `ops`, where `ops[i]` is the `ith` operation you must apply to the record and is one of the following:

1. An integer `x` - Record a new score of `x`.
2. `"+"` - Record a new score that is the sum of the previous two scores. It is guaranteed there will always be two previous scores.
3. `"D"` - Record a new score that is double the previous score. It is guaranteed there will always be a previous score.
4. `"C"` - Invalidate the previous score, removing it from the record. It is guaranteed there will always be a previous score.

Return *the sum of all the scores on the record*.

 

**Example 1:**

```
Input: ops = ["5","2","C","D","+"]
Output: 30
Explanation:
"5" - Add 5 to the record, record is now [5].
"2" - Add 2 to the record, record is now [5, 2].
"C" - Invalidate and remove the previous score, record is now [5].
"D" - Add 2 * 5 = 10 to the record, record is now [5, 10].
"+" - Add 5 + 10 = 15 to the record, record is now [5, 10, 15].
The total sum is 5 + 10 + 15 = 30.
```

**Example 2:**

```
Input: ops = ["5","-2","4","C","D","9","+","+"]
Output: 27
Explanation:
"5" - Add 5 to the record, record is now [5].
"-2" - Add -2 to the record, record is now [5, -2].
"4" - Add 4 to the record, record is now [5, -2, 4].
"C" - Invalidate and remove the previous score, record is now [5, -2].
"D" - Add 2 * -2 = -4 to the record, record is now [5, -2, -4].
"9" - Add 9 to the record, record is now [5, -2, -4, 9].
"+" - Add -4 + 9 = 5 to the record, record is now [5, -2, -4, 9, 5].
"+" - Add 9 + 5 = 14 to the record, record is now [5, -2, -4, 9, 5, 14].
The total sum is 5 + -2 + -4 + 9 + 5 + 14 = 27.
```

**Example 3:**

```
Input: ops = ["1"]
Output: 1
```

 

**Constraints:**

- `1 <= ops.length <= 1000`
- `ops[i]` is `"C"`, `"D"`, `"+"`, or a string representing an integer in the range `[-3 * 104, 3 * 104]`.
- For operation `"+"`, there will always be at least two previous scores on the record.
- For operations `"C"` and `"D"`, there will always be at least one previous score on the record.

## 题目大意

给定一系列字符串表示操作数和数字，

规则如下：

* 如果是数字，就添加一个数字，
* 如果是 “+”，就添加一个数字，是前两个数字之和，
* 如果是“D”，就添加一个数字，是前一个数字的而两倍
* 如果是“C”，就删除最后一个数字

## 解题思路

* 这道题可以用栈来模拟，可以使用 STL 的stack，也可以使用数组来进行模拟。

## 代码

````c++
class Solution {
public:
    // 解法一：使用栈来完成
    /*
    int calPoints(vector<string>& ops) {
        stack<string> sta;
        
        for (string str : ops) {
            if (str == "C") {
                sta.pop();
            } else if (str == "D") {
                sta.push(to_string(2 * stoi(sta.top())));
            } else if (str == "+") {
                // FIXME 可以继续优化，这里的效率比较低
                int last = stoi(sta.top());
                sta.pop();
                
                int tmp = stoi(sta.top()) + last;
                
                sta.push(to_string(last));
                sta.push(to_string(tmp));
            } else {
                sta.push(str);
            }
        }
        
        int res = 0;
        while (!sta.empty()) {
            int tmp = stoi(sta.top());
            sta.pop();
            res += tmp;
        }
        
        return res;
    }*/
    
    // 解法二：使用数组来模拟栈，来优化“+”符号需要弹出的操作
    int calPoints(vector<string>& opt) {
        vector<string> sta;
        
        for (string str : opt) {
            if ( str == "C") {
                sta.pop_back();
            } else if (str == "D") {
                sta.push_back(to_string(2 * stoi(sta.back())));
            } else if (str == "+") {
                int tmp = stoi(sta[sta.size() - 1]) + stoi(sta[sta.size() - 2]);
                
                sta.push_back(to_string(tmp));
            } else {
                sta.push_back(str);
            }
        }
        
        int res = 0;
        for (string str : sta) {
            res += stoi(str);
        }
        return res;
    }
};
````

