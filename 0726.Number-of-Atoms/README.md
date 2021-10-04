# [726. Number of Atoms](https://leetcode.com/problems/number-of-atoms/)

Given a string `formula` representing a chemical formula, return *the count of each atom*.

The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.

One or more digits representing that element's count may follow if the count is greater than `1`. If the count is `1`, no digits will follow.

- For example, `"H2O"` and `"H2O2"` are possible, but `"H1O2"` is impossible.

Two formulas are concatenated together to produce another formula.

- For example, `"H2O2He3Mg4"` is also a formula.

A formula placed in parentheses, and a count (optionally added) is also a formula.

- For example, `"(H2O2)"` and `"(H2O2)3"` are formulas.

Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than `1`), followed by the second name (in sorted order), followed by its count (if that count is more than `1`), and so on.

 

**Example 1:**

```
Input: formula = "H2O"
Output: "H2O"
Explanation: The count of elements are {'H': 2, 'O': 1}.
```

**Example 2:**

```
Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
```

**Example 3:**

```
Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
```

**Example 4:**

```
Input: formula = "Be32"
Output: "Be32"
```

 

**Constraints:**

- `1 <= formula.length <= 1000`
- `formula` consists of English letters, digits, `'('`, and `')'`.
- `formula` is always valid.
- All the values in the output will fit in a 32-bit integer.

## 解题思路

给定一个表示化学式的字符串，返回其中原子的个数。

原子总是以大写字母开头，0 个或者多个小写字母，

如果这个元素的数量比1 大，后面就跟一位或者多位数字表述数量，如果数量是1，后面没有数字，

* 例如，"H2O" 和 "H2O2" 是可行的，但 "H1O2" 这个表达是不可行的。

两个化学式连在一起可以构成新的化学式。

* 例如 "H2O2He3Mg4" 也是化学式。

由括号括起的化学式并佐以数字（可选择性添加）也是化学式。

* 例如 "(H2O2)" 和 "(H2O2)3" 是化学式。

返回所有原子的数量，格式为：第一个（按字典序）原子的名字，跟着它的数量（如果数量大于 1），然后是第二个原子的名字（按字典序），跟着它的数量（如果数量大于 1），以此类推。

## 解题思路

### 解法1

这种解法可以参考这篇题解：https://leetcode-cn.com/problems/number-of-atoms/solution/gong-shui-san-xie-shi-yong-xiao-ji-qiao-l5ak4/



````c++
class Solution {
public:
    string countOfAtoms(string formula) {
        unordered_map<string, int> cnt;
        stack<string> sta;  // 这里存储的是字符串
        
        int idx = 0;
        int i = 0;
        while (i < formula.size()) {
            // 如果是括号直接入栈
            if (formula[i] == '(' || formula[i] == ')') {
                sta.push(string(1, formula[i]));
                i++;
            } else {
                if (isdigit(formula[i])) {
                    // 计算数字
                    int freq = 0;
                    while (i < formula.size() && isdigit(formula[i])) {
                        freq = freq * 10 + static_cast<int>(formula[i] - '0');
                        i++;
                    }
                    
                    if (!sta.empty() && sta.top() == ")") {
                        sta.pop(); // pop ")"
                        
                        // 存储这个数字可以起作用的所有原子
                        vector<string> tmp;
                        
                        // 处理一对括号中的所有元素
                        while (!sta.empty() && sta.top() != "(") {
                            string name = sta.top();
                            sta.pop();
                            
                            cnt[name] *= freq;
                            
                            tmp.push_back(name);
                        }
                        sta.pop();  // 弹出 "("
                        
                        // 将所有的字符串添加回去
                        for (int j = tmp.size() - 1; j >= 0; j--) {
                            sta.push(tmp[j]);
                        }
                    } else {
                        // 如果只对一个原子有效，就只影响这一个原子
                        if (!sta.empty()) {
                            string name = sta.top();
                            sta.pop();
                            
                            cnt[name] *= freq;
                            
                            sta.push(name);
                        }
                    }
                } else {
                    // 得到一个处理过的原子名
                    string name = "";
                    name.push_back(formula[i]);  // 首字母是大写
                    i++;
                    // 加上后面的小写字母
                    while (i < formula.size() && islower(formula[i])) {
                        name.push_back(formula[i]);
                        i++;
                    }
                    name.push_back('_');
                    name += to_string(idx);
                    idx++;
                    cnt.insert(make_pair(name, 1));
                    sta.push(name);
                }
            }
        }
        
        // 合并不同的版本号的相同原子
        // 这里利用了 map 的有序性
        map<string, int> atoms;
        for (auto& item : cnt) {
            string name = "";
            string str = item.first;
            for (int i = 0; i < str.size() && str[i] != '_'; i++) {
                name.push_back(str[i]);
            }
            atoms[name] += item.second;       
        }
        
        string res = "";
        for (auto& item : atoms) {
            res += item.first;
            // 只有原子数大于 1，才添加数字
            if (item.second > 1) {
                res += to_string(item.second);
            }
        }
        
        return res;
    }
};
````

