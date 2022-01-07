# [386. Lexicographical Numbers](https://leetcode.com/problems/lexicographical-numbers/)

## 题目

Given an integer `n`, return all the numbers in the range `[1, n]` sorted in lexicographical order.

You must write an algorithm that runs in `O(n)` time and uses `O(1)` extra space. 

 

**Example 1:**

```
Input: n = 13
Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]
```

**Example 2:**

```
Input: n = 2
Output: [1,2]
```

 

**Constraints:**

- `1 <= n <= 5 * 104`



## 题目大意

给定一个整数 n，返回 按照字典序排列的`[1, n]`

你必须在 O(n) 的复杂度，并使用 O(1)的空间，

## 解题思路

这道题可以参考这篇题解：https://leetcode-cn.com/problems/lexicographical-numbers/solution/386-zi-dian-xu-pai-shu-o1-kong-jian-fu-z-aea2/

你可以把这个过程转化为多叉树的前序遍历

### Solution 1:  暴力解法

这种解法比较无脑，将数字转化为字符串，排序后再转化为整数，

```c++
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<string> strs(n);
        for (int i = 0; i < n; ++i) {
            // 将整数先转化为字符串
            strs[i] = to_string(i + 1);
        }
        // 对字符串按照字典序排序
        sort(strs.begin(), strs.end());
        
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            // 再转化为整数
            res[i] = stoi(strs[i]);
        }
        
        return res;
    }
};
```

### Solution 2: DFS

````c++
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        for (int i = 1; i < 10; ++i) {
            DFS(i, n);
        }
        return res_;
    }
    
 private:
    vector<int> res_;
    
    void DFS(int num, int n) {
        if (num > n) {
            return;
        }
        
        res_.push_back(num);
        for (int i = 0; i < 10; ++i) {
            // 每次递归，都是更深一层
            DFS(num * 10 + i, n);
        }
    }
};
````

### Solution 3: 迭代

一般来说递归改迭代需要用到栈来维持状态，就这道题目而言的话，也可以不用栈来维持状态，

```c++
class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> res;
        
        int num = 1;
        while (res.size() < n) {
            while (num <= n) {
                // 不断往下
                res.push_back(num);
                num *= 10;
            }
            
            while (num % 10 == 9 || num > n) {
                // 如果当前层已经遍历完,
                // 1、遍历到 9
                // 2、超过
                num /= 10;
            }
            // 同一层的下一个节点
            ++num;
        }
        
        return res;
    }
};
```

