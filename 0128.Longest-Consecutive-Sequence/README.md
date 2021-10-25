# [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)

## 题目

Given an unsorted array of integers `nums`, return *the length of the longest consecutive elements sequence.*

You must write an algorithm that runs in `O(n)` time.

 

**Example 1:**

```
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
```

**Example 2:**

```
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
```

 

**Constraints:**

- `0 <= nums.length <= 105`
- `-109 <= nums[i] <= 109`

## 题目大意

给定一个未排序的整数数组，返回最长的连续序列的长度

你必须在(n) 的时间解决

## 解题思路

* 这道题的关键在于将相邻的两个数合并，初始化时，我们将数组中的每个元素加入到集合中，
* 这道题使用的 加权的quick-union 算法
* 这道题目只需要改变 Union 方法，使之返回每次连通后，新的连通分量的大小，

## 代码

`````c++
class UF {
 public:
    UF(const vector<int>& nums) {
        for (int num : nums) {
            parent_.insert(make_pair(num, num));
            len_.insert(make_pair(num, 1));
        }
    }

    bool Connected(int p, int q) {
        return Find(p) == Find(q);
    }

    int Find(int p) {
        while (p != parent_[p]) {
            // 这里实现路径压缩
            parent_[p] = parent_[parent_[p]];
            p = parent_[p];
        }
        return p;
    }

    // 返回合并之后，连通分量的大小
    int Union(int p, int q) {
        int proot = Find(p);
        int qroot = Find(q);

        if (proot == qroot) {
            return 0;
        }

        int psize = len_[proot];
        int qsize = len_[qroot];

       if (psize < qsize) {
            parent_[proot] = qroot;
            len_[qroot] = psize + qsize;
       } else {
            parent_[qroot] = proot;
            len_[proot] = psize + qsize;
       }
       return psize + qsize;
    }

    bool Exist(int p) {
        return parent_.find(p) != parent_.end();
    }

 private:
    // 这道题目的数据是离散的，所以选择哈希表更好一些，
    unordered_map<int, int> parent_;
    // 维护以当前节点为根的节点总数（包括根）
    unordered_map<int, int> len_;
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        
        UF uf(nums);
        
        int res = 1;
        for (int num : nums) {
            if (uf.Exist(num - 1)) {
                res = max(res, uf.Union(num, num - 1));
            }
            
            if (uf.Exist(num + 1)) {
                res = max(res, uf.Union(num, num + 1));
            }
        }
        
        return res;
    }
};
`````

