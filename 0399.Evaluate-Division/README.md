# [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/) 

## 题目

You are given an array of variable pairs `equations` and an array of real numbers `values`, where `equations[i] = [Ai, Bi]` and `values[i]` represent the equation `Ai / Bi = values[i]`. Each `Ai` or `Bi` is a string that represents a single variable.

You are also given some `queries`, where `queries[j] = [Cj, Dj]` represents the `jth` query where you must find the answer for `Cj / Dj = ?`.

Return *the answers to all queries*. If a single answer cannot be determined, return `-1.0`.

**Note:** The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

 

**Example 1:**

```
Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
```

**Example 2:**

```
Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
```

**Example 3:**

```
Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
```

 

**Constraints:**

- `1 <= equations.length <= 20`
- `equations[i].length == 2`
- `1 <= Ai.length, Bi.length <= 5`
- `values.length == equations.length`
- `0.0 < values[i] <= 20.0`
- `1 <= queries.length <= 20`
- `queries[i].length == 2`
- `1 <= Cj.length, Dj.length <= 5`
- `Ai, Bi, Cj, Dj` consist of lower case English letters and digits.

## 题目大意

给定一个变量对方程数组 equations，和一个实数数组 values，其中 equations[i] = [Ai, Bi], 和 values[i] 共同表示等式 Ai / Bi = values[i], 每个 Ai 和 Bi 是一个表示表示单个变量的字符串，

另给定一个数组 queries ，其中 queries[j] = [Cj, Dj],表示 第 j 个查询，你必须找出Cj / Dj 的结果，

返回所有问题的答案，如果这个问题没有答案，返回 -1.0，

## 解题思路

* 这道题目依旧是用并查集来解决，不过这道题需要做一个由字符串到并查集中的元素的转换，此外并查集中需要添加一个额外的数组来保存子节点和父节点之间的倍数关系，
* 这道题目可以参考这篇题解：https://www.yuque.com/liweiwei1419/algo/seywro

## 代码

````c++
class UF {
 public:
    UF(int n) {
        parent_.resize(n);
        weight_.resize(n);
        
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
            weight_[i] = 1.0;
        }
    }
    
    // 递归版路径压缩
    int Find(int p) {
        if (p != parent_[p]) {
            // 这里需要维护 weight_ 的意义
            int origin = parent_[p];
            parent_[p] = Find(parent_[p]);
            weight_[p] *= weight_[origin];
        }
        
        return parent_[p];  // 这里只有返回 parent_[p]才能做到递归
    }
    
    double Connected(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);
        
        if (proot == qroot) {
            return weight_[p] / weight_[q]; // 这里表示查到了
        } else {
            return -1.0;
        }
    }
    
    void Union(int p, int q, double value) {
        int proot = Find(p);
        int qroot = Find(q);
        parent_[proot] = qroot;
        weight_[proot] = weight_[q] * value / weight_[p];   // 重新计算 proot 的权重
    }
    
 private:
    vector<int> parent_;
    vector<double> weight_; // 这里我们增加一个权重，用来表示子节点是父节点的几倍
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values, vector<vector<string>>& queries) {
        int len = equations.size();
        unordered_map<string, int> hash;    // 从字符串到整数的映射
        UF uf(2 * len);
        
        // 建立一个有向图
        int id = 0;
        for (int i = 0; i < len; ++i) {
            string str1 = equations[i][0];
            string str2 = equations[i][1];
            
            if (hash.find(str1) == hash.end()) {
                hash.insert(make_pair(str1, id));
                ++id;
            }
            
            if (hash.find(str2) == hash.end()) {
                hash.insert(make_pair(str2, id));
                ++id;
            }
            uf.Union(hash[str1], hash[str2], values[i]); // 将字符串转化为对应的 ID，放入连通分量当中
        }
        
        vector<double> res;
        for (int i = 0; i < queries.size(); ++i) {
            string str1 = queries[i][0];
            string str2 = queries[i][1];
            
            if (hash.find(str1) == hash.end()
               || hash.find(str2) == hash.end()) {
                res.push_back(-1.0);
            } else {
                int id1 = hash.at(str1);
                int id2 = hash.at(str2);
                
                res.push_back(uf.Connected(id1, id2));
            }
        }
        
        return res;
    }
};
````

