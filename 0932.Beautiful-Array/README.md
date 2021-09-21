# [932. Beautiful Array](https://leetcode.com/problems/beautiful-array/)

## 题目

An array `nums` of length `n` is **beautiful** if:

- `nums` is a permutation of the integers in the range `[1, n]`.
- For every `0 <= i < j < n`, there is no index `k` with `i < k < j` where `2 * nums[k] == nums[i] + nums[j]`.

Given the integer `n`, return *any **beautiful** array* `nums` *of length* `n`. There will be at least one valid answer for the given `n`.

 

**Example 1:**

```
Input: n = 4
Output: [2,1,4,3]
```

**Example 2:**

```
Input: n = 5
Output: [3,1,2,5,4]
```

 

**Constraints:**

- `1 <= n <= 1000`

## 题目大意

一个长度为 n 的数组是 漂亮的如果：

* 数组 num 是 [1, n] 的全排列
* 对于每个 0 <= i < j < n，都没有满足 i < k < j，其中 2 * nums[k] == nums[i] + nums[j]。

给定长度 n，返回长度为n 的漂亮数组，对于给定的 n ，只是有一个有效的答案，

## 解题思路

* 这道题目也是一道分治，不过难度确实超过我的想象了，这里贴上一篇题解：https://leetcode-cn.com/problems/beautiful-array/solution/c-fen-zhi-fa-dai-tu-pian-jie-shi-by-avphn4vwuo/还有这一篇：https://leetcode-cn.com/problems/beautiful-array/solution/fen-zhi-mei-guan-jie-na-yao-xuan-hu-geng-syo6/
* 题目中有个条件 2 * nums[k] ==  nums[i] + nums[j]，左侧一定是一个偶数，如果要让这个等式成立，就必须满足 奇数 = 偶数 + 奇数，所以我们只需要将数组的左侧设置为奇数，右侧设置为 偶数即可，
* 这道题目需要一些数序知识，目前我还太菜了，以后补上

## 代码

`````c++
class Solution {
public:
    vector<int> beautifulArray(int n) {
        return Divi(n);
    }
    
 private:
    unordered_map<int, vector<int>> cache;
    
    vector<int> Divi(int n) {
        vector<int> res(n, 0);
        int t = 0;	// res 数组的下标
        if (cache.find(n) != cache.end()) {
            return cache[n];
        }
        
        if (n != 1) {
            // 这里注意 (n + 1) / 2 + n / 2 = n，因为除法是向下取整
            // 所以这里左边要比右边多一个元素，
            for (auto it : Divi((n + 1) / 2)) {
                res[t++] = 2 * it - 1;
            }
            
            for (auto it : Divi(n / 2)) {
                res[t++] = 2 * it;
            }
        } else {
            res[0] = 1;
        }
        
        cache[n] = res;
        return res;
    }
};
`````

