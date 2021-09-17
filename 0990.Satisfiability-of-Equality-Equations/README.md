# [990. Satisfiability of Equality Equations](https://leetcode.com/problems/satisfiability-of-equality-equations/)

## 题目

You are given an array of strings `equations` that represent relationships between variables where each string `equations[i]` is of length `4` and takes one of two different forms: `"xi==yi"` or `"xi!=yi"`.Here, `xi` and `yi` are lowercase letters (not necessarily different) that represent one-letter variable names.

Return `true` *if it is possible to assign integers to variable names so as to satisfy all the given equations, or* `false` *otherwise*.

 

**Example 1:**

```
Input: equations = ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.
```

**Example 2:**

```
Input: equations = ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
```

**Example 3:**

```
Input: equations = ["a==b","b==c","a==c"]
Output: true
```

**Example 4:**

```
Input: equations = ["a==b","b!=c","c==a"]
Output: false
```

**Example 5:**

```
Input: equations = ["c==c","b==d","x!=z"]
Output: true
```

 

**Constraints:**

- `1 <= equations.length <= 500`
- `equations[i].length == 4`
- `equations[i][0]` is a lowercase letter.
- `equations[i][1]` is either `'='` or `'!'`.
- `equations[i][2]` is `'='`.
- `equations[i][3]` is a lowercase letter.

## 题目大意

给定一个表示两个变量之间关系的字符方程组成的数组，，每个字符串方程equations[i]的长度为 4，采用两种不同的形式之一，“xi==yi” 或 “xi!=yi”。在这里，xi 和 yi 是小写字母（不一定不同），表示单字母变量名,

如果可以将整数赋给单字母变量来满足这个方程，就返回 true，否则就返回 false，

## 解题思路

* 这道题目可以用并查集来解决，
* 将相等的单字母变量连接到一起，然后如果后面又出现不相等的关系，则直接返回错误，

## 代码

`````c++
class UF {
 public:
    UF(int size) {
        id_.resize(size);
        for (int i = 0; i < size; ++i) {
            id_[i] = i;
        }
    }

    bool Connected(int p, int q) {
        return Find(p) == Find(q);
    }

    int Find(int p) {
        while (p != id_[p]) {
            id_[p] = id_[id_[p]];
            p = id_[p];
        }
        return p;
    }

    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);

        id_[proot] = qroot;
    }

 private:
    vector<int> id_;
};

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UF uf(26);

        for (const string& str : equations) {
            if (str[1] == '=') {
                int p = str[0] - 'a';
                int q = str[3] - 'a';
                uf.Union(p, q); // 确定一种关系，
            }
        }

        for (const string& str : equations) {
            if (str[1] == '!') {
                int p = str[0] - 'a';
                int q = str[3] - 'a';

                if (uf.Connected(p, q)) {   // 发生矛盾，出错
                    return false;
                }
            }
        }
        return true;
    }
};
`````

