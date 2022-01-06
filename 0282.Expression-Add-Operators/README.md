# [282. Expression Add Operators](https://leetcode-cn.com/problems/expression-add-operators/)

## 题目

Given a string `num` that contains only digits and an integer `target`, return ***all possibilities** to insert the binary operators* `'+'`*,* `'-'`*, and/or* `'*'` *between the digits of* `num` *so that the resultant expression evaluates to the* `target` *value*.

Note that operands in the returned expressions **should not** contain leading zeros.

 

**Example 1:**

```
Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
```

**Example 2:**

```
Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.
```

**Example 3:**

```
Input: num = "105", target = 5
Output: ["1*0+5","10-5"]
Explanation: Both "1*0+5" and "10-5" evaluate to 5.
Note that "1-05" is not a valid expression because the 5 has a leading zero.
```

**Example 4:**

```
Input: num = "00", target = 0
Output: ["0*0","0+0","0-0"]
Explanation: "0*0", "0+0", and "0-0" all evaluate to 0.
Note that "00" is not a valid expression because the 0 has a leading zero.
```

**Example 5:**

```
Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
```

 

**Constraints:**

- `1 <= num.length <= 10`
- `num` consists of only digits.
- `-231 <= target <= 231 - 1`

## 题目大意

给定一个只含有数字的字符串 num 和一个整数 target，返回所有向这个表达式中添加二元运算符使得表达式的值为 target，注意在返回的表达式中不能包含前导 0，

## 解题思路

首先可以发现，这道题目是可以使用回溯来做的，每两个字符之间的关系有四种：加、减、✖️、“”，另外，这个数的范围存在负数，所以这里也需要注意对符号的处理，

这里重要的是切分出不同长度的数，并进行不同的运算，

### Solution 1:DFS

这种解法，可以参考这篇题解：https://leetcode-cn.com/problems/expression-add-operators/solution/gong-shui-san-xie-hui-su-suan-fa-yun-yon-nl9z/

```c++
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        DFS(target, num, 0, 0L, 0L, "");
        return res_;
    }
    
 private:
    vector<string> res_;
    
    void DFS(int target, const string& num, int idx, long prev, long cur, string path) {
        if (idx == num.size()) {
            if (target == cur) {
                res_.push_back(path);
            }
            return;
        }
        
        const int len = num.size();
        for (int i = idx; i < len; ++i) {
            if (i != idx && num[idx] == '0') {
                // 这里是为了处理前导 0
                continue;
            }
            long next = stol(num.substr(idx, i - idx + 1)); //  切分出要使用的数字
            // 进行递归
            if (idx == 0) {
                // 特殊处理
                DFS(target, num, i + 1, next, next, "" + to_string(next));
            } else {
                DFS(target, num, i + 1, next, cur + next, path + '+' + to_string(next)); // 加法
                DFS(target, num, i + 1, -1 * next, cur - next, path + '-' + to_string(next)); // 减法
                long tmp = prev * next;
                DFS(target, num, i + 1, tmp, cur - prev + tmp, path + '*' + to_string(next)); // 乘法
            }
        }
    }
};
```







