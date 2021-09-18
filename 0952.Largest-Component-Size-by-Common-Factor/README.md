# [952. Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/)

## 题目

You are given an integer array of unique positive integers `nums`. Consider the following graph:

- There are `nums.length` nodes, labeled `nums[0]` to `nums[nums.length - 1]`,
- There is an undirected edge between `nums[i]` and `nums[j]` if `nums[i]` and `nums[j]` share a common factor greater than `1`.

Return *the size of the largest connected component in the graph*.

 

**Example 1:**

![img](https://assets.leetcode.com/uploads/2018/12/01/ex1.png)

```
Input: nums = [4,6,15,35]
Output: 4
```

**Example 2:**

![img](https://assets.leetcode.com/uploads/2018/12/01/ex2.png)

```
Input: nums = [20,50,9,63]
Output: 2
```

**Example 3:**

![img](https://assets.leetcode.com/uploads/2018/12/01/ex3.png)

```
Input: nums = [2,3,6,7,4,12,21,39]
Output: 8
```

 

**Constraints:**

- `1 <= nums.length <= 2 * 104`
- `1 <= nums[i] <= 105`
- All the values of `nums` are **unique**.

## 题目大意

给定一个整数数组（不包含重复数字），考虑下面的图：

* 有 nums.length 个节点，按照从 nums[i] 到 nums[nums.lenght - 1]列出
* 如果 nums[i] 和 nums[j] 有一个大于1 的最大公约数，则这两个节点之间有一条无向边，

返回途中最大的连通组件

## 解题思路

* 这道题提到了连通性，所以直觉上就可以使用 并查集来解决
* 先就建立一个并查集，对数组中的每个数，求出其所有的因式，构成连通分量
* 再次遍历数组，统计各个连通分量代表元出现的次数，就是最终的结果

## 代码

````c++
class UF {
 public:
    UF(int n)
        : parent_(vector<int>(n)) {
        for (int i = 0; i < n; ++i) {
            parent_[i] = i;
        }        
    }
    
    int Find(int p) {
        while (p != parent_[p]) {
            parent_[p] = parent_[parent_[p]];
            p = parent_[p];
        }
        return p;
    }
    
    void Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);
        
        if (proot != qroot) {
            parent_[proot] = qroot;
        }
    }
    
 private:
    vector<int> parent_;
};

class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int val = 0;
        for (int num : nums) {
            val = max(val, num);
        }
        
        UF uf(val + 1); // 0 位置不用，因此需要加 1，
        
        // 先建图
        for (int num : nums) {
            double upper = sqrt(num);
            for (int i = 2; i <= upper; ++i) {
                if (num % i == 0) {
                    uf.Union(num, i);   // 一次计算一对数，当然而这可能相同
                    uf.Union(num, num / i);
                }
            }
        }
        
        // 将候选数组映射为代表元，统计代表元出现的次数，找出最大者
        vector<int> cnt(val + 1);
        int res = 0;
        for (int num : nums) {
            int root = uf.Find(num);
            ++cnt[root];
            res = max(res, cnt[root]);
        }
        
        return res;
    }
};
````

