# [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)

## 题目

The set `[1, 2, 3, ..., n]` contains a total of `n!` unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for `n = 3`:

1. `"123"`
2. `"132"`
3. `"213"`
4. `"231"`
5. `"312"`
6. `"321"`

Given `n` and `k`, return the `kth` permutation sequence.

 

**Example 1:**

```
Input: n = 3, k = 3
Output: "213"
```

**Example 2:**

```
Input: n = 4, k = 9
Output: "2314"
```

**Example 3:**

```
Input: n = 3, k = 1
Output: "123"
```

 

**Constraints:**

- `1 <= n <= 9`
- `1 <= k <= n!`

## 题目大意

集合 [1, 2, 3, ..., n] 共含有 n! 中排列，按照特定的顺序返回第 k 个排列，

* 1 <= n <= 9
* 1 <= k <= n!

## 解题思路

* 这是一道排列的题目，必须要进行剪枝，不能直接暴力列出所有，
* 这里放上一篇比较好的题解：https://leetcode-cn.com/problems/permutation-sequence/solution/hui-su-jian-zhi-python-dai-ma-java-dai-ma-by-liwei/

## 代码

````c++
/*
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<bool> used(n, false);
        Backtracking(n, &k, used);
        return res.str();
    }
    
 private:
    stringstream res;
    vector<int> path;
    
    void Backtracking(int n, int *k, vector<bool>& used) {
        if (path.size() == n) {
            if (--*k == 0) {
                // for (int j = 0; j < path.size(); ++j) {
                //     res += to_string(path[j]);
                // }
                copy(path.begin(), path.end(), ostream_iterator<int>(res));
            }
            return;
        }
        
        for (int i = 1; i <= n; ++i) {
            if (!used[i - 1]) {
                path.push_back(i);
                used[i - 1] = true;
                Backtracking(n, k, used);
                used[i - 1] = false;
                path.pop_back();
            }
        }
    }
};*/

class Solution {
 public:
    string getPermutation(int n, int k) {
        vector<bool> used(n + 1, false);
        vector<int> factorial(std::move(CalcFactorial(n)));
        Backtracking(n, k, used, factorial);
        return res;
    }
    
 private:
    string res;
    
    vector<int> CalcFactorial(int n) {
        vector<int> nums(n + 1);
        nums[0] = 1;
        for (int i = 1; i <= n; ++i) {
            nums[i] = nums[i - 1] * i;
        }
        return nums;
    }
    
    void Backtracking(int n, int k, vector<bool>& used, vector<int>& factorial) {
        if (res.size() == n) {
            return; // 已经得到结果，直接返回
        }
        
        int rem_fac = factorial[n - 1 - res.size()];    // 剩下的树的全排列数
        for (int i = 1; i <= n; ++i) {
            if (used[i]) {
                continue;
            }
            
            if (rem_fac > 0 && rem_fac < k) { // 如果剩下的数的递归数小于 k，则第 k 个排列肯定不再当前递归
                k -= rem_fac;
                continue;   // 剪枝
            }
            
            res += to_string(i);
            used[i] = true;
            Backtracking(n, k, used, factorial);
            // 因为是一次递归直接着找到结果，所以不用回溯，否则最终结果就是空了
        }
    }
};
````

