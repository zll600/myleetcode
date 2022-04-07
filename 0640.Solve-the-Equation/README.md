# [640. Solve the Equation](https://leetcode-cn.com/problems/solve-the-equation/)

## 题目

Solve a given equation and return the value of `'x'` in the form of a string `"x=#value"`. The equation contains only `'+'`, `'-'` operation, the variable `'x'` and its coefficient. You should return `"No solution"` if there is no solution for the equation, or `"Infinite solutions"` if there are infinite solutions for the equation.

If there is exactly one solution for the equation, we ensure that the value of `'x'` is an integer.

 

**Example 1:**

```
Input: equation = "x+5-3+x=6+x-2"
Output: "x=2"
```

**Example 2:**

```
Input: equation = "x=x"
Output: "Infinite solutions"
```

**Example 3:**

```
Input: equation = "2x=x"
Output: "x=0"
```

 

**Constraints:**

- `3 <= equation.length <= 1000`
- `equation` has exactly one `'='`.
- `equation` consists of integers with an absolute value in the range `[0, 100]` without any leading zeros, and the variable `'x'`.

## 题目大意

求解一个给定的方程，将 `x` 以字符串 `"x=#value"` 的形式返回。该方程仅包含 `'+' ， '-' `操作，变量 `x` 和其 *对应系数* 。

如果方程没有解，请返回 `"No solution"` 。如果方程有 *无限解* ，则返回 `“Infinite solutions”`  。

如果方程中只有一个解，要保证返回值 `'x'` 是一个整数。

## 解题思路

这道题就是使用模拟数学中解法，将 x 和常数分别移动到等号两侧，然后进行 判断就可以了：

- 如果两侧都为 0 ，那么就是无穷解
- 如果x 一侧为 0,但是常数项不为 0，那么就是无解
- 其余情况，正常解

### Solution 1:

这种解法可以参考 [这篇题解](https://leetcode-cn.com/problems/solve-the-equation/solution/640-cchao-100de-shu-xue-jie-fa-by-ffretu-lfw0/)

````c++
class Solution {
public:
    string solveEquation(string equation) {
        // 根据 '=' 分割等式
        auto pos = equation.find('=');
        // 因式分解
        vector<string> lhs = SplitEquation(equation.substr(0, pos));
        vector<string> rhs = SplitEquation(equation.substr(pos + 1));

        // x 的系数
        int lhs_cnt = 0;
        // 其他项
        int rhs_cnt = 0;

        for (string& str : lhs) {
            if (str.find('x') != string::npos) {
                lhs_cnt += GetCoefficient(str);
            } else {
                rhs_cnt -= stoi(str);
            }
        }

        for (string& str : rhs) {
            if (str.find('x') != string::npos) {
                lhs_cnt -= GetCoefficient(str);
            } else {
                rhs_cnt += stoi(str);
            }
        }

        if (lhs_cnt == 0 && rhs_cnt == 0) {
            return "Infinite solutions";
        } else if (lhs_cnt == 0 && rhs_cnt != 0) {
            return "No solution";
        }

        return "x=" + to_string(rhs_cnt / lhs_cnt);
    }

 private:
    // 分割每一项
    vector<string> SplitEquation(const string& equation) {
        vector<string> res;
        string last = "";

        for (char c : equation) {
            if (c == '+' || c == '-') {
                if (!last.empty()) {
                    res.push_back(last);
                }
                last = c;
            } else {
                last += c;
            }
        }
        // 最后一组不要忘记加入到集合中
        res.push_back(last);

        return res;
    }

    // 获取 x 的系数
    int GetCoefficient(string& word) {
        const int len = word.size();
        if (len > 1 && isdigit(word[len - 2])) {
            // 如果系数大于 1，那么将 x 置换为 ' '
            std::replace(word.begin(), word.end(), 'x', ' ');
        } else {
            // 如果系数等于 1，此时 x 前面应该没有系数那么将 x 置换为 '1'
            std::replace(word.begin(), word.end(), 'x', '1');
        }

        return stoi(word);
    }
};
````
